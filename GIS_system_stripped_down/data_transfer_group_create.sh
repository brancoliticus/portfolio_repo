sudo addgroup data_transfer_group
sudo adduser postgres data_transfer_group
sudo adduser ubuntu data_transfer_group
sudo chgrp -R data_transfer_group /home/ubuntu/Desktop/data_transfer_folder
sudo su postgres
