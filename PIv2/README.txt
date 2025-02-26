command to make virtual enviroment on PI:
python -m venv --system-site-packages .env

command to configure stable ssh over ethernet:
sudo nmcli connection modify "Wired connection 1" ipv4.method manual ipv4.address 192.168.0.8/24

check for running project:
ps aux | grep plattCode | grep -v grep

command to kill running project:
sudo pkill -9 plattCode


needed pip moduals to install on both PIs

name                     purple           pink

sparkfun-qwiic-otos 
setproctitle   