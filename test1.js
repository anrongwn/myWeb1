(function () {
    var isfinished=false;

    var head= document.getElementsByTagName('body')[0];
    var script= document.createElement('script');
    script.type= 'text/javascript';
    script.src= './msgutils.js';
    script.onload=function(){
        isfinished=true;
    }

    script.onreadystatechange = function () {
    if (this.readyState === 'complete')
        isfinished=true;
    }

    head.appendChild(script);


    /*
    while(!isfinished){

    }
    */
})();

