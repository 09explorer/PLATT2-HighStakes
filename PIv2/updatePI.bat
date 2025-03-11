ssh -p 22 %1@%1.local "sudo pkill -9 plattCode; sudo rm -rf /home/%1/platt/active"
scp -r %~dp0active %1@%1.local:/home/%1/platt
::ssh -p 22 %1@%1.local "sudo nohup /home/%1/platt/.env/bin/python /home/%1/platt/active/runAuton.py > /dev/null 2>&1 &"
ssh -t %1@%1.local "sudo nohup /home/%1/platt/.env/bin/python /home/%1/platt/active/main.py &"
pause