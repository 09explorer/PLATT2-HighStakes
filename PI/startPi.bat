ssh -p 22 %1@%1.local "sudo nohup /home/%1/platt/.env/bin/python /home/%1/platt/active/runAuton.py > /dev/null 2>&1 &"
pause