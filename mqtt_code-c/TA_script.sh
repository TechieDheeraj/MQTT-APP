#!/bin/bash/
name="mack"
port_mos=5555
host_mos="12.0.0.2"
topic_sub="/ta/$name"
topic_keepalive=proto_msg 
topic_res=proto_msg 
topic_bin=proto_msg 
rm TA"$name".log
rm "$name"success
	
	./keepalive -m "1223 1 $name " -p $port_mos -t $topic_keepalive -h $host_mos
	data=`./test-sub $host_mos $port_mos $topic_sub`
	echo $data
	set -- $data
	echo transactionid $1;
        echo ta_name $2;
        echo messagetype $3;
        echo test_duration $4;
        echo result_duration $5;
        echo binary_name $6;
        echo binary_argument_list $7;
	echo ?=$?
	bin=$6
	echo $bin
	./${bin}  $4 $5 $1 $2 $port_mos $topic_bin $host_mos $7  &
	sleep 5
	x=`pgrep ${bin}`
	echo ?=$?
	if [ "$x" == "" ] 
	then
		echo "_____________________________$6 NOT RUNNING__________________________________________"
		./info -name $name -m "$1 2 FAILED payload" -p $port_mos -t $topic_bin -h $host_mos 
	else
		echo "_____________________________$6  RUNNING______________________________________________"
		./info -name $name -m "$1 2 RUNNING payload" -p $port_mos -t $topic_bin -h $host_mos 
		echo ?=$?
	fi
	
	Duration=$4 		
	let "Duration-=5"
	while [ $Duration -gt 0 ]
	do
		echo in_while
		x=`pgrep ${bin}`
		if [  -z "$x"  ] 
		then
			echo "________________________________________________________________$bin FAILED"
			./info -name $name -m "$1 3 FAILURE 0" -p $port_mos -t $topic_bin -h $host_mos
			exit
		fi
		
		sleep 5
		let "Duration-=5"

	done
	echo "TA TERMINATED SUCCESSFULLY"

