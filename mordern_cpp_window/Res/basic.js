/////////////////////////////////////////////////////////////////////////////
//===========================================================================
function test0(str) {
	alert(str);
	
	var result = "JS에서 넘김";
	
	return result;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
function coreEntry() {

	var button1 = document.getElementById("button1");
	var button2 = document.getElementById("button2");



	button1.addEventListener("click", 
		function() {
			alert("Hello world");
		}
	);

	button2.addEventListener("click", 
		function() {
			var s;
			
			var eventName;

			var paramName;
			var paramValue;
			var paramPair;

			var queryString;


			paramName = encodeURIComponent("변수1"); // utf8
			paramValue = encodeURIComponent("값1");
			paramPair = paramName + "=" + paramValue;


			queryString = paramPair;


			paramName = encodeURIComponent("변수2");
			paramValue = encodeURIComponent("값2&");
			paramPair = paramName + "=" + paramValue;


			queryString += "&";
			queryString += paramPair;


			eventName = "버튼2 클릭 이벤트";


			if (queryString)
			{
				s =  eventName + "?" + queryString;
			}


			window.location.href = s;
		}
	);


	var rv;


	rv = test0("JS에서 부름");
	alert(rv);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
window.onload = function () {
  coreEntry();
}
