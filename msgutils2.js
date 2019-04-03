var context;
function init(){
    new QWebChannel(qt.webChannelTransport, function(channel){context = channel.objects.context;});
    document.getElementById("bn1").onclick=onBtnSendMsg;
};
function onBtnSendMsg(){
    var cmd = document.getElementById("in1").value;sendMessage(cmd);
};
function sendMessage(msg){
    context.onMsg(1, msg);
};
function recvMessage(msg){
    var obj = document.getElementById("in1");
    obj.value=msg;
    return "index.html--recvMessage";
};
init();
