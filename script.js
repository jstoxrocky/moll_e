$(document).ready(function() {

	$("body").append("<p>Loading Moll-E.</p>");
	$("head").append("<style type='text/css' src=''></style>");
	$("body").append("<div></div>")


	var keys = "";
	var k = "";
	var kDic = {};


	$(document).keydown(function (e) {

		
		if (e.which == 65) {
			k = "a";
		} else if (e.which == 87) {
			k = "w";
		} else if (e.which == 83) {
			k = "s";
		} else if (e.which == 68) {
			k = "d";
		}

		kDic[k] = true;
	    keys = keys + k;
	    kString = ""

	    $.each(Object.keys(kDic), function(i, v) {
			kString = kString + v;
		});

	    console.log(kString);
	    $.post('/forward', kString, function(data) { 	 
        	});

	});

	$(document).keyup(function (e) {
		$.post('/forward', "stop", function(data) { 	 
        	});
    	keys = "";
    	kDic = {};
	});


	$("body").append("<p>Load complete.</p>");


});  