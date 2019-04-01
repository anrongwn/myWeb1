var context;
// 初始化
function init()
{
    if (typeof QWebChannel != 'undefined')
    {
        new QWebChannel(qt.webChannelTransport, function(channel)
        {
        context = channel.objects.context;
        }
        );
    }
    else
    {
        alert("qt对象获取失败！");
    }
}
// 向qt发送消息
function sendMessage(msg)
{
    if(typeof context == 'undefined')
    {
        alert("context对象获取失败！");
    }
    else
    {
        context.onMsg(1, msg);
    }
}
// 控件控制函数
function onBtnSendMsg()
{
    var cmd = document.getElementById("in1").value;
    sendMessage(cmd);
}

function onTest(){
    var obj = document.getElementById("in1");
    if (typeof obj === 'undefined'){
    }else{
        obj.value="2000";
    }
}

//
function getResult(){
    var obj = document.getElementById("in1");
    var result="None";

    if (typeof obj === 'undefined'){
        result="None";
    }else{
        result = obj.value;
    }

    return result;
}

// 接收qt发送的消息
function recvMessage(msg)
{
    //alert("接收到Qt发送的消息：" + msg);
    var obj = document.getElementById("in1");
    if (typeof obj === 'undefined'){
        alert("obj === 'undefined'" + msg);
    }else{
        //alert("接收到Qt发送的消息1：" + msg);
        obj.value=msg;
    }

    return "index.html--recvMessage";
}


function getCookie(c_name)
{
    if (document.cookie.length>0)
    {
        c_start=document.cookie.indexOf(c_name + "=")
        if (c_start!=-1)
        {
            c_start=c_start + c_name.length+1
            c_end=document.cookie.indexOf(";",c_start)
            if (c_end==-1) c_end=document.cookie.length
            return unescape(document.cookie.substring(c_start,c_end))
        }
    }
    return ""
}

window.onload=function(){
    var amount = getCookie("amount");

    if (amount===""){
        //alert("getCookie(amount)==null" );
    }

    document.getElementById("in1").value=amount;

}

init();
