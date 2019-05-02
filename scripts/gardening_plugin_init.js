// JavaScript Document

$(document).ready(function () {
    console.log("INIT PLUGIN");
    jQuery(".remote_plugin_main").gardening_manage({nodemcu: "http://192.168.1.20:80/gardening"});
});
