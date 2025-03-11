ssh -p 22 %1@%1.local "sudo pkill -9 plattCode; sudo nohup /home/%1/platt/.env/bin/python /home/%1/platt/active/main.py"
pause
