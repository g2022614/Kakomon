$(window).load(function () {

    var mainArea = $("#main");
    var sideWrap = $("#side");
    var sideArea = $("#fixedmenu");
    
    var wd = $(window); 
	
    var mainH = mainArea.height();
    var sideH = sideWrap.height();
    
    
    if(sideH < mainH) { 
		sideWrap.css({"height": mainH,"position": "relative"});
	var sideOver = wd.height()-sideArea.height();
	var starPoint = sideArea.offset().top + (-sideOver);
	var breakPoint = sideArea.offset().top + mainH;
	var flag1 = 0;
	
	wd.scroll(function() {
	    
	    if(wd.height() < sideArea.height()){
		flag1 = 0;


		if(starPoint < wd.scrollTop() && wd.scrollTop() + wd.height() < breakPoint){
		    sideArea.css({"position": "fixed", "bottom": "20%"}); 
				    sideArea.css("margin-top","10px");
		}else if(wd.scrollTop() + wd.height() >= breakPoint){
		    sideArea.css({"position": "absolute", "bottom": "0"});
		    
		} else {
		    sideArea.css("position","absolute");

		}
		
	    }else{
		var sideBtm = wd.scrollTop() + sideArea.height();

 		
		if(mainArea.offset().top < wd.scrollTop() && sideBtm < breakPoint){
		    sideArea.css({"position": "fixed", "top": "10px"});
		    sideArea.css("margin-top","10px");
		}else if(sideBtm >= breakPoint){
		    var fixedSide = mainH - sideH;
		    sideArea.css({"position": "absolute", "top": fixedSide});
		    
		} else {
		    sideArea.css("position","absolute");		    
 		    sideArea.css("margin-top","30%");

		}
	    }
	    
	    
	});
	
    } 
    
});
