Required libraries
wxWidgets

apt-key adv --fetch-keys https://repos.codelite.org/CodeLite.asc

sudo apt-add-repository 'deb https://repos.codelite.org/wx3.1.5/ubuntu/ focal universe'

sudo apt-get update
sudo apt-get install libwxbase3.1-0-unofficial
sudo apt-get install libwxbase3.1unofficial-dev
sudo apt-get install libwxgtk3.1-0-unofficial
sudo apt-get install libwxgtk3.1unofficial-dev
sudo apt-get install wx3.1-headers
sudo apt-get install wx-common
sudo apt-get install libwxgtk-webview3.1-0-unofficial

sudo apt-get install libwxbase3.1-0-unofficial-dbg  
sudo apt-get install libwxgtk3.1-0-unofficial-dbg 
sudo apt-get install libwxgtk-webview3.1-0-unofficial-dbg
sudo apt-get install libwxgtk-media3.1-0-unofficial-dbg 



sudo apt install zlib1g
sudo apt install zlib1g-dev