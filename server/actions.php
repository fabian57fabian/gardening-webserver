<?php

    /*
	REQUIRE:
	
	
    CREATE TABLE `waterlevels` (
      `id` int NOT NULL auto_increment,
      `value` varchar(50) NOT null,
      `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
      PRIMARY KEY (`id`)
    ) ENGINE=InnoDB, auto_increment=1;
    */

	/* setta il formato di risposta */
	header('Content-Type: text/json');
	require_once("config.php");
	$action = $_POST['action'];

	/* conterrà la stringa di query al database */
	$query_string = "";

	
	/* smista secondo il tipo di richiesta */
	switch($action) {
		case "addWaterLevel":
		    addWaterLevel();
		break;
	}

	function addWaterLevel(){
		//TODO: finish this
    }

?>