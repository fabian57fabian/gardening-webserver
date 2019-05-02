DROP DATABASE IF EXISTS `home_auto`;
CREATE DATABASE `home_auto`;

use `home_auto`;

DROP TABLE IF EXISTS `waterlevels` ;

CREATE TABLE `waterlevels` (
  `id` int NOT NULL auto_increment,
  `value` varchar(50) NOT null,
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB, auto_increment=1;