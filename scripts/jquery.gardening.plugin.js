// JavaScript Document

(function ($) {
        $.fn.gardening_manage = function (options) {

            console.log("Nodemcu link: " + options['nodemcu']);


            var i;
            for (i = 2; i <= 20; i++) {
                $("#water_times").append($('<option>', {
                    value: i * 1000,
                    text: i + " seconds"
                }));
            }

            $("#send_water").on("click", function () {
                gestisciInvia($('#water_times option:selected').val());
            });


            function fadeMessage(message) {
                $(".result_box p").fadeOut(function () {
                    $(this).text(message).fadeIn();
                });
            }

            function gestisciInvia(water_time) {
                console.log("Sending water command");
                var request = $.ajax({
                    url: options.nodemcu,
                    type: "POST",
                    data: {"plain": "{\"action\": \"annaffia\", \"time\": \"" + water_time + "\"}"},
                    dataType: "json"
                });
                request.done(function (result) {
                    console.log("Water action done: " + result['status']);
                    var d=new Date;
                    fadeMessage(d.getHours() + "."+ d.getMinutes() +":"+ d.getSeconds() +" - "+ result['status']);
                });
                request.fail(
                    function (jqXHR, textStatus) {
                        console.log("Failed to send water action");
                    }
                );
            }
        }
    }
)
(jQuery);
