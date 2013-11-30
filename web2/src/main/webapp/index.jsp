<html>


    <head>
        <script src="jquery-2.0.3.min.js"></script>
        <script type="text/javascript">
            function sendJSON(obj) {
                $.post("/web2/hello", JSON.stringify(obj),
                        function (data){
                            $('body').html(data);
                         }
                );
            }

        </script>
    </head>

        <body >

            <input type="text" id="1" value="1"/>
            <input type="text" id="2" value="2"/>

        <button onclick="sendJSON({'field1':$('#1').val(),'filed2':$('#2').val()})">  json send  </button>
    </body>

</html>
