<html>
<head><title>GUI</title></head>
<body >

<div id = "screen" style="background-color:#EEEEEE;height:400px;width:400px;float:left;">
    <canvas id="canvas" width="400" height="400" >
        This text is displayed if your browser does not support HTML5 Canvas.
    </canvas>
</div>

<div id = "createdGeomObj" style="background-color:orange;height:400px;width:100px;float:left;" >
    <h5> Created Geometrical Objects</h5>
</div>

<div id = "geomObj" style="background-color:blue;height:400px;width:100px;float:left;">
    <h5> Geometrical objects</h5>
    <p> <input type="button" value="parabola" onclick="addGeomObj( new Parabola(-1,1,1) )"> </p>
    <p> <input type="button" value="arc" onclick="addGeomObj(new Arc(1,0,Math.PI) )"> </p>
    <p> <input type="button" value="line" onclick="addGeomObj(new Line(-1,1) )"> </p>
</div>

<div id = "submit" style = "background-color:red;height:100px;width:100px;float:left;">
    <form onsubmit="getAction(this)" method="post">
        <input type="submit" value = "SUBMIT">
    </form>
</div>

<div id = "geomObjParam" style="height:100;width:500;clear:both"> </div>

<script type="text/javascript">
// globals
var canvas = document.getElementById('canvas');
var context = canvas.getContext('2d');
var width = context.canvas.width;
var height = context.canvas.height;
var thickness = 3;
var axisArrowLength = 15;
var maxX = 5;
var maxY = 5;
context.lineWidth = thickness;
var nameToGeomParam = {};
var parabolaNum = 0;
var usualColor = 'red';
var markedColor = 'green';

function getAction(form) {
    form.action = "/SimpleWebApp/results?parabola=99";
}
function getURL() {

    var params = "";
  /*  for (var name in nameToGeomParam) {
        params += name + "=";
        for (var param in nameToGeomParam[name].params) {
            params += param + "=" + nameToGeomParam[name].params[param];
        }
        params + "&";
    }      */
    return params;
}
function Point(x,y) {
    this.x = parseFloat(x);
    this.y = parseFloat(y);
}

function Parabola(Ax, Bx, b) {
    //the static variable counter
    if (typeof  Parabola.number == 'undefined') {
        Parabola.number=0;
    }
    else {
        Parabola.number++;
    }
    this.No = Parabola.number;
    this.params = {Ax: parseFloat(Ax), Bx: parseFloat(Bx), b:parseFloat(b)};
    this.paint = paint;
    this.name = "parabola" + this.No;

    function paint(color) {       //parabola y(x) = b*x^2 between points A and B. Ax, Bx - abscissa in Cartesian
        var Ax = this.params.Ax;
        var Bx = this.params.Bx;
        var b = this.params.b;
        var Ay = b * Ax * Ax;     //Ay in Cartesian
        var By = b*Bx*Bx;     //By in Cartesian
        // control point is intersection of two tangential to end-points A and B
        controlX = (Ax + Bx) / (2);
        controlY = Ay + 2*b*Ax*(controlX - Ax);   //value of tangential to point A at control point
        context.beginPath();
        context.moveTo(fromCartesianX(Ax), fromCartesianY(Ay));
        context.strokeStyle = color;
        context.quadraticCurveTo(fromCartesianX(controlX),fromCartesianY(controlY), fromCartesianX(Bx), fromCartesianY(By));
        context.stroke();
        context.closePath();
    }
}


function Arc(radius, angle1, angle2) {
    //the static variable counter
    if (typeof  Arc.number == 'undefined') {
        Arc.number=0;
    }
    else {
        Arc.number++;
    }

    this.No = Arc.number;
    this.params = {radius: parseFloat(radius), angle1 : parseFloat(angle1), angle2 : parseFloat(angle2)};
    this.paint = paint;
    this.name = "Arc" + this.No;

    function paint(color) {
        context.beginPath();
        context.strokeStyle = color;
        context.arc(fromCartesianX(0), fromCartesianX(0), toPixelWidth(this.params.radius), this.params.angle1, this.params.angle2);
        context.stroke();
        context.closePath();
    }
}

function Line(Ax, Bx) {
    //the static variable counter
    if (typeof  Line.number == 'undefined') {
        Line.number=0;
    }
    else {
        Line.number++;
    }

    this.No = Line.number;
    this.params = { Ax: parseFloat(Ax), Bx: parseFloat(Bx) };
    this.name = "Line" + this.No;
    this.paint = paint;

    function paint(color) {
        context.beginPath();
        context.strokeStyle = color;
        context.moveTo(fromCartesianX(this.params.Ax), fromCartesianX(0));
        context.lineTo(fromCartesianX(this.params.Bx), fromCartesianX(0));
        context.stroke();
        context.closePath();
    }
}

function addTextField(parentElement, value, label) {
    var labelElement = document.createElement("label");
    labelElement.innerHTML = label + ": "
    parentElement.appendChild(labelElement);
    var textFieldElement = document.createElement("input");
    textFieldElement.type = "text";
    textFieldElement.value = value;
    textFieldElement.className = label;
    textFieldElement.size = 10;
    parentElement.appendChild(textFieldElement);
}

function deleteChildren(parentElement) {
    if (parentElement.hasChildNodes()) {
        while (parentElement.hasChildNodes()) {
            parentElement.removeChild(parentElement.lastChild);
        }
    }
}
function showGeomObjParam(geomObjName) {
    if (nameToGeomParam.hasOwnProperty(geomObjName) ) {
        markGeomObj(geomObjName);
        var paramsElement = document.getElementById("geomObjParam");
        // delete all children elements
        deleteChildren(document.getElementById("geomObjParam"));
        header = document.createElement("h5");
        header.innerHTML = nameToGeomParam[geomObjName].name + ": ";
        paramsElement.appendChild(header);
        //labelElement.innerHTML = nameToGeomParam[geomObjName].name + ": "
        var params = nameToGeomParam[geomObjName].params;
        for (var key in params) {
            addTextField(paramsElement, params[key], key);
        }

        //button "Ok" to approve the parabola parameters modification
        var buttonOk = document.createElement("input");
        buttonOk.type = "button";
        buttonOk.value = "Ok";
        getValue = "document.getElementById('geomObjParam').getElementsByClassName";
        buttonOk.setAttribute("onclick","modifyGeomObjParams('" + geomObjName + "')");
        paramsElement.appendChild(buttonOk);

        //button to delete geometrical object
        var buttonDelete = document.createElement("input");
        buttonDelete.type = "button";
        buttonDelete.value = "delete";
        buttonDelete.setAttribute("onclick", "deleteGeomObj('" + geomObjName + "')");
        paramsElement.appendChild(buttonDelete);
    }
    else {
        alert ("Error during execution showGeomObjParam(). There is no geometrical object " +
                geomObjName + " in the nameToGeomParam map");
    }
}


//put modified parameters from text fields in section "Modify geometrical object" to
// the geometrical object with name "GeomObj"
function modifyGeomObjParams(geomObjName) {
    if (nameToGeomParam.hasOwnProperty(geomObjName)) {
        var modifiedParams = nameToGeomParam[geomObjName].params;
        for (var key in modifiedParams) {
            modifiedParams[key] = parseFloat(document.getElementById('geomObjParam').getElementsByClassName(key)[0].value);
        }
        markGeomObj(geomObjName);
    }
    else {
        alert("Error in modifyGeomObj(). There is no the geometrical object " + geomObjName + " in the nameToGeomParam map");
    }
}

function deleteGeomObj(geomObjName) {
    if (nameToGeomParam.hasOwnProperty(geomObjName)) {
        var geomObjList = document.getElementById("createdGeomObj");
        geomObjNameButton = geomObjList.getElementsByClassName(geomObjName)[0];
        geomObjList.removeChild(geomObjNameButton);
        delete nameToGeomParam[geomObjName];
        deleteChildren( document.getElementById("geomObjParam") );    //delete content of the Section "Modify Geom Object"
        repaint();
    }
    else {
        alert("there is no geometrical object " + geomObjName);
    }
}

function addGeomObjButton(geomObjName) {
    var geomObjList = document.getElementById("createdGeomObj");
    var geomObjNameButton = document.createElement("input");
    geomObjNameButton.type = "button";
    geomObjNameButton.value = geomObjName;
    geomObjNameButton.className = geomObjName;
    geomObjNameButton.onclick =  "showGeomObjParam( geomObjName )";// "showGeomObjParam('" + geomObjName + "')";
    geomObjNameButton.setAttribute("onclick", "showGeomObjParam('" + geomObjName + "')");
    geomObjList.appendChild(geomObjNameButton);
    var p = document.createElement("p");
    geomObjList.appendChild(p);
}

function repaint() {    //repaint all geometrical objects.
    clearScreen();
    paintAxes();
    for (var name in nameToGeomParam) {
        nameToGeomParam[name].paint('red');
    }
}

function markGeomObj(geomObjName) {
    repaint();
    nameToGeomParam[geomObjName].paint('green');
}

function showGeomObj() {
    context.font = "italic 12px Times New Roman";
    var calc = 0;
    for (var key in nameToGeomParam) {
        calc++;
        context.fillText("Geom obj : " + key + " Ax : " + nameToGeomParam[key].Ax +
                " Bx : " + nameToGeomParam[key].Bx + " b : " + nameToGeomParam[key].b, 30,30 + calc*15);
    }
}

function toPixelWidth(cartesianWidth) {
    return width/(2*maxX)*cartesianWidth;
}

function fromCartesianX(x) {
    return width/(2*maxX)*(x + maxX);
}

function fromCartesianY(y) {
    return height/(2*maxY)*(maxY - y);
}

function toCartesianX(x_) {
    return 2*maxX/width*x_ - maxX;
}

function toCartesianY(y_) {
    return maxY - 2*maxY/height*y_
}

function paintAxes() {
    context.beginPath();
    context.strokeStyle = "black";
    context.moveTo(0,height/2); context.lineTo(width,height/2);     // X axis
    context.lineTo(width-axisArrowLength, height/2+axisArrowLength);//buttom part of Y axis arrow
    context.moveTo(width-axisArrowLength, height/2-axisArrowLength);
    context.lineTo(width,height/2);                                 //top part of Y axis arrow
    context.moveTo(width/2,0);    context.lineTo(width/2,height);   // Y axis
    context.moveTo(width/2 - axisArrowLength, axisArrowLength);
    context.lineTo(width/2,0);                                      //left part of X axis arrow
    context.moveTo(width/2 + axisArrowLength, axisArrowLength);
    context.lineTo(width/2,0);                                       //left part of X axis arrow
    context.stroke();
    context.font = "italic 16px Times New Roman";
    context.fillText("X", width - 2*axisArrowLength, height/2 + axisArrowLength);
    context.fillText("Y", width/2 - axisArrowLength, 2*axisArrowLength);
    context.fillText("O", width/2 -  axisArrowLength, width/2 + axisArrowLength)
    context.closePath();
}

function clearScreen() {
    context.beginPath();
    context.clearRect(0,0,width, height);
    context.closePath();
    context.stroke();
}


function addGeomObj(geomObj) {
    nameToGeomParam[geomObj.name] = geomObj;
    repaint();
    addGeomObjButton(geomObj.name);
    document.getElementById("createdGeomObj").getElementsByClassName(geomObj.name)[0].click();
}

paintAxes();
</script>

</body>
</html>