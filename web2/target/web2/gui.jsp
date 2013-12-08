<html>
<head>
    <script src="jquery-2.0.3.min.js"></script>
    <title>GUI</title>
</head>
<body >

<div id = "screen" style="background-color:#EEEEEE;height:400px;width:400px;float:left;">
    <canvas id="canvas" width="400" height="400" >
        This text is displayed if your browser does not support HTML5 Canvas.
    </canvas>
</div>

<div id = "createdGeomObj" style="background-color:orange;height:400px;width:100px;float:left;" >
    <h5> Created Geometrical Objects</h5>
    <select id = "userObjects" name="select" style="width: 100px;" >
    </select>
</div>


<div id = "geomObj" style="background-color:blue;height:400px;width:100px;float:left;">
    <h5> Geometrical objects</h5>
    <p> <input type="button" value="parabola" onclick="addGeomObj( new Parabola(-1,1,1) )"> </p>
    <p> <input type="button" value="arc" onclick="addGeomObj(new Arc(1,0,Math.PI) )"> </p>
    <p> <input type="button" value="line" onclick="addGeomObj(new Line(-1,1) )"> </p>
</div>

<div id = "submit" style = "background-color:red;height:100px;width:100px;float:left;">
    <button onclick="sendJSON(nameToGeomParam['parabola0'].params)">  json Rambo send  </button>


</div>

<div id = "geomObjParam" style="height:100;width:500;clear:both"> </div>


<div id = "result" style="height:100;width:500;clear:both"> </div>

<script type="text/javascript">

function sendJSON (obj) {

    alert('ax:'+obj.ax+'bx:'+obj.bx+'b:'+obj.b);
    $.ajax({
            type: "POST",
            contentType: "application/json; charset=utf-8",
            url: "/web2/rest/hello2",
            data:   JSON.stringify( obj ),
            //dataType: "json",
            success: function(response){
                alert(response);
                $("#result").append( $("<h5>").text(response) ) ;
            }
        });


}

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

//______________________Geometrical Objects (web view)____________________________________________________
function showGeomObjParam(geomObjName) {
    if (nameToGeomParam.hasOwnProperty(geomObjName) ) {
        markGeomObj(geomObjName);

        $("#geomObjParam").empty();           //remove all child of previous geomObjParam

        $("#geomObjParam").append( $("<h5>").text(geomObjName) );

        var params = nameToGeomParam[geomObjName].params;
        for (var key in params) {
            $("#geomObjParam").append($("<label>").text(key + ": "));
            $("#geomObjParam").append( $('<input type = "text">').val(params[key]).addClass(key).css("width",100) );
        }

        //button "Ok" to approve the parabola parameters modification
        var buttonOk = $("<button>Ok</button>").click(function() { modifyGeomObjParams(geomObjName); });
        buttonOk.appendTo("#geomObjParam");

        //button to delete geometrical object
        var buttonDel = $("<button>Delete</button>").click(function() { deleteGeomObj(geomObjName); });
        buttonDel.appendTo("#geomObjParam");
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

        var x=$('#userObjects')[0];
        x.remove(x.selectedIndex);        //remove option in selectUserObject

        delete nameToGeomParam[geomObjName];

        $("#geomObjParam").empty();       //remove all child

        repaint();
    }
    else {
        alert("there is no geometrical object " + geomObjName);
    }
}

function addGeomObjOption(geomObjName) {
    var option = $('<option value = geomObjName id = geomObjName></option>').html(geomObjName)
            .click(function() {showGeomObjParam( geomObjName )} );
    option.appendTo("#userObjects");
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


//______________________Geometrical Objects (Model and Canvas View) ____________________________________________________
function Point(x,y) {
    this.x = parseFloat(x);
    this.y = parseFloat(y);
}

function Parabola(ax, bx, b) {

    //the static variable counter
    if (typeof  Parabola.number == 'undefined') {
        Parabola.number=0;
    }
    else {
        Parabola.number++;
    }
    this.No = Parabola.number;
    this.params = {ax: parseFloat(ax), bx: parseFloat(bx), b:parseFloat(b)};

    this.paint = paint;
    this.name = "parabola" + this.No;

    function paint(color) {       //parabola y(x) = b*x^2 between points A and B. Ax, Bx - abscissa in Cartesian
         var ax = this.params.ax;
        var bx = this.params.bx;
        var b = this.params.b;
        var ay = b * ax * ax;     //Ay in Cartesian
        var by = b*bx*bx;     //By in Cartesian
        // control point is intersection of two tangential to end-points A and B
        controlX = (ax + bx) / (2);
        controlY = ay + 2*b*ax*(controlX - ax);   //value of tangential to point A at control point
        context.beginPath();
        context.moveTo(fromCartesianX(ax), fromCartesianY(ay));
        context.strokeStyle = color;
        context.quadraticCurveTo(fromCartesianX(controlX),fromCartesianY(controlY), fromCartesianX(bx), fromCartesianY(by));
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

function Line(ax, bx) {
    //the static variable counter
    if (typeof  Line.number == 'undefined') {
        Line.number=0;
    }
    else {
        Line.number++;
    }

    this.No = Line.number;
    this.params = { ax: parseFloat(ax), bx: parseFloat(bx) };
    this.name = "Line" + this.No;
    this.paint = paint;

    function paint(color) {
        context.beginPath();
        context.strokeStyle = color;
        context.moveTo(fromCartesianX(this.params.ax), fromCartesianX(0));
        context.lineTo(fromCartesianX(this.params.bx), fromCartesianX(0));
        context.stroke();
        context.closePath();
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
    addGeomObjOption(geomObj.name);
    document.getElementById("createdGeomObj").getElementsByClassName(geomObj.name)[0].click();
}

paintAxes();
</script>

</body>
</html>