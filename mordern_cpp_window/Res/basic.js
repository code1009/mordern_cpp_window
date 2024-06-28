/////////////////////////////////////////////////////////////////////////////
//===========================================================================
function test0(str) {
	alert(str);
	
	var result = "JS에서 넘김";
	
	return result;
}

/////////////////////////////////////////////////////////////////////////////
//===========================================================================
/*
IWebBrowser2지원 안됨
class MyCanvas {
	constructor(de) {
		this.documentElement = de;
		this.ctx = this.documentElement.getContext("2d");

		this.ctx.fillStyle = "white";
		this.ctx.fillRect(0, 0, this.documentElement.width, this.documentElement.height);
	}

	draw() {		
		this.ctx.beginPath();
		this.ctx.arc(95, 50, 40, 0, 2 * Math.PI);
		this.ctx.stroke();
	}

	draw2() {		
		this.ctx.moveTo(0, 0);
		this.ctx.lineTo(200, 100);
		this.ctx.stroke();
	}
}
*/



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
let _myCanvas;
let _myCanvas_Ctx;

function draw() {
	_myCanvas_Ctx.beginPath();
	_myCanvas_Ctx.arc(95, 50, 40, 0, 2 * Math.PI);
	_myCanvas_Ctx.stroke();
}

function draw2() {		
	_myCanvas_Ctx.moveTo(0, 0);
	_myCanvas_Ctx.lineTo(200, 100);
	_myCanvas_Ctx.stroke();
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
function coreEntry() {
	let myCanvasDocElement = document.getElementById("myCanvas");
	_myCanvas_Ctx = myCanvasDocElement.getContext("2d");
	draw();

	/*
	let myCanvasDocElement = document.getElementById("myCanvas");
	_myCanvas = new MyCanvas(myCanvasDocElement);
	_myCanvas.draw();
	*/


	var button1 = document.getElementById("button1");
	var button2 = document.getElementById("button2");


	button1.addEventListener("click", 
		function() {
			alert("Hello world");

			//_myCanvas.draw2();
			draw2();
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
