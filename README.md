
Required libraries
wxWidgets

apt-key adv --fetch-keys https://repos.codelite.org/CodeLite.asc

sudo apt-add-repository 'deb https://repos.codelite.org/wx3.1.5/ubuntu/ focal universe'

sudo apt-get update
apt-get install libwxbase3.1-0-unofficial \
                libwxbase3.1unofficial-dev \
                libwxgtk3.1-0-unofficial \
                libwxgtk3.1unofficial-dev \
                wx3.1-headers \
                wx-common \