ssh -p 22 %1@%1.local "sudo pkill -9 PlattCode; rm -rf /home/%1/plattifornia/active"
scp -r %~dp0active %1@%1.local:/home/%1/plattifornia
ssh -p 22 %1@%1.local "nohup sudo nohup /home/%1/plattifornia/.env/bin/python /home/%1/plattifornia/active/test.py > /dev/null 2>&1 &"