#!/bin/bash
echo "##################"
echo "###缺页中断统计###"
echo "##################"
#统计开始缺页次数
start=$(awk 'NR==6{print$17}' /proc/stat)
echo "请输入统计时长:"
#读取睡眠时间，睡眠时间由用户决定
read time
sleep $time 
end=$(awk 'NR==6{print$17}' /proc/stat)
#end-start为这段时间内的缺页中断次数
outcome=`expr $end - $start`
echo "缺页次数为${outcome}次"


