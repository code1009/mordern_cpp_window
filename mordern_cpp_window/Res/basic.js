/////////////////////////////////////////////////////////////////////////////
//===========================================================================
function coreEntry() {

	var button1 = document.getElementById("button1");



	button1.addEventListener("click", 
		function(){
			alert("Hello world");
		}
	)
}

function test0() {
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
window.onload = function () {
  coreEntry();
}