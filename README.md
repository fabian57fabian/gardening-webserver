

# gardening-webserver-apache

<p align="center"> 
<img src="https://github.com/fabian57fabian/gardening-webserver/blob/master/images/pianta_in_vaso.png">
</p>

This is a project to mantain a User Interface for gardening controlling purposes.
Since the last update we can control the watering pomp sending messages to a webserver on a NodeMCU v3 controller.

## Installation

To install gardening-webserver you have to install mysql (or phpmyadmin, mariadb, postgresql...). 
Once you've done that add an user with a specified password (the default one i am using is client1 with password client1password). 
Next you have to login into the database and execute the commands inside create_table.sql file.

Next you'll have to upload the webserver code for the NodeMCU controller.

Enjoy!
