ssh -p 22 %1@%1.local "sudo pkill -9 PlattCode; sudo /home/%1/platt/.env/bin/python /home/%1/platt/active/runAuton.py"
pause