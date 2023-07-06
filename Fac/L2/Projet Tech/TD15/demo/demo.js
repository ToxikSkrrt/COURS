// Demo Canvas (JavaScript)

/* ******************** global variables ******************** */

var canvas = document.getElementById('mycanvas');

// load mario image
var mario = new Image();
mario.src = "mario.png";

// load custom image
var customImage = new Image();
customImage.src = "touka.jpg";

// initial position in canvas
var marioX = 100;
var marioY = 100;
var squareX = 300;
var squareY = 300;
var customImageX = 200;
var customImageY = 200;

/* ******************** register events ******************** */

window.addEventListener('load', windowLoad);              // window load
canvas.addEventListener('click', canvasLeftClick);        // left click event
canvas.addEventListener('contextmenu', canvasRightClick); // right click event
window.addEventListener('keyup', canvasKeyPressed);  // pressed key event

/* ******************** event callback ******************** */

function canvasLeftClick(event) {
    event.preventDefault(); // prevent default context menu to appear...
    // get relative cursor position in canvas
    console.log("left click at position:", event.offsetX, event.offsetY);
    // update position of mario image used by drawCanvas()
    marioX = event.offsetX;
    marioY = event.offsetY;
    drawCanvas();
}

function canvasRightClick(event) {
    event.preventDefault(); // prevent default context menu to appear...
    // get relative cursor position in canvas
    console.log("right click at position:", event.offsetX, event.offsetY);
    // update position of mario image used by drawCanvas()
    squareX = event.offsetX;
    squareY = event.offsetY;
    drawCanvas();
}

function canvasKeyPressed(event) {
    event.preventDefault(); // prevent default context menu to appear...
    // update position of custom image used by drawCanvas()
    if (event.code == "ArrowUp") {
        console.log("ArrowUp pressed");
        customImageY -= 10;
    }
    else if (event.code == "ArrowDown") {
        console.log("ArrowDown pressed");
        customImageY += 10;
    }
    else if (event.code == "ArrowLeft") {
        console.log("ArrowLeft pressed");
        customImageX -= 10;
    }
    else if (event.code == "ArrowRight") {
        console.log("ArrowRight pressed");
        customImageX += 10;
    }

    drawCanvas();
}

function callFibo() {
    var n = parseInt(document.getElementById('n').value);
    const result = Module._fibo(n);
    var elem = document.getElementById('result');
    elem.innerHTML = `<p> Result: ${result} </p>`;
}

function windowLoad() {
    console.log("window load");
    drawCanvas();
}

/* ******************** canvas drawing ******************** */

function drawCanvas() {
    var ctx = canvas.getContext('2d');
    var width = canvas.width;
    var height = canvas.height;

    // clear canvas
    ctx.clearRect(0, 0, width, height);

    // draw a yellow square at (squareX, squareY) position
    ctx.save();
    ctx.fillStyle = 'yellow';
    ctx.fillRect(squareX, squareY, 40, 40);
    ctx.restore();

    // draw some lines
    ctx.save();
    ctx.strokeStyle = 'blue';
    ctx.moveTo(0, 0);
    ctx.lineTo(width, height);
    ctx.moveTo(width, 0);
    ctx.lineTo(0, height);
    ctx.stroke(); // the stroke will actually paint the current lines
    ctx.restore();

    // draw a centered text
    ctx.save();
    ctx.font = 'bold 20px Arial';
    ctx.fillStyle = 'black';
    ctx.textBaseline = 'middle';
    ctx.textAlign = 'center';
    ctx.fillText("Hello World!", width / 2, height / 2);
    ctx.restore();

    // draw mario image at (marioX, marioY) position
    ctx.drawImage(mario, marioX, marioY, 80, 80);
    // draw custom image at (customImageX, customImageY) position
    ctx.drawImage(customImage, customImageX, customImageY, 80, 80);
}

// EOF
