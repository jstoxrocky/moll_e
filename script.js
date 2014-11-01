$(document).ready(function() {

	//DEBUG TEST LOCALLY
	// $("head").append("<link href='style.css' rel='stylesheet' type='text/css'>");
	
	//RUN ON ARDUINO
	$("head").append("<link href='https://rawgit.com/joestox/moll_e/master/style.css' rel='stylesheet' type='text/css'>");
	
	$("body").append("<div id='title'><p>Moll-E 1.0</p></div>");
		

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
	    $.post('/f', kString, function(data) { 	 
        	});

	});

	// $(document).keyup(function (e) {
	// 	$.post('/forward', "stop", function(data) { 	 
 //        	});
 //    	keys = "";
 //    	kDic = {};
	// });


		//let Arduino know page is loaded
		$.post('/f', '1', function(data) { 	 
	        	});



});  