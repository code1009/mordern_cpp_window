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
			window.location.href = "event1";
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
