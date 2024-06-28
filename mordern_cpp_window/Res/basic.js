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
		function(){
			alert("Hello world");
		}
	)
	
	
	button2.addEventListener("click", 

		function(){
			window.location.href = "test";
			
/*
			if(window.window == document.parentWindow)
			{
			alert("button2");
			}
			window.postMessage('Hello from the same window!', '*');
*/
/*
basic.js:35 Uncaught TypeError: Cannot read properties of undefined (reading 'postMessage')
    at HTMLInputElement.<anonymous> (basic.js:35:26)

			document.parentWindow.postMessage('Hello from the same window!', '*');
*/
		}
	)

/*
basic.js:39 Uncaught TypeError: Cannot set properties of undefined (setting 'onmessage')
    at coreEntry (basic.js:39:34)
    at window.onload (basic.js:66:3)

	document.parentWindow.onmessage = 
		function(v){
			alert("parentWindow.onmessage");
		};
*/

/*
	window.onmessage = 
		function(event) {
			alert("onmessage(): " + event.data);
		};
*/

	var x = test0("JS에서 부름");
	alert(x);
	
	
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
window.onload = function () {
  coreEntry();
}
