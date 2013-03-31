var annie_highlightText_mouse = false;
var annie_highlightShowing = true;

jQuery(document).ready(function()
{
	jQuery('#annie_highlightTextBox, #annie_toolbox').hover(function() {
        annie_highlightText_mouse = true; 
    }, function() {
        annie_highlightText_mouse = false; 
    });
    
    jQuery("body").keydown(function(e) {
    
		if (e.keyCode == 27 && jQuery('#annie_highlightTextBox').is(":visible"))
		{
			annie_hideHighlights();
		}
	});

    jQuery("body").mouseup(function() { 
        if(!annie_highlightText_mouse)
        	annie_hideHighlights();
    });
    
    jQuery('#annie_toolbox').attr('unselectable', 'on')
	.css({
		'-moz-user-select':'none',
		'-webkit-user-select':'none',
		'user-select':'none',
		'-ms-user-select':'none'
	}).each(function() {
		this.onselectstart = function() { return false; };
	});
});

function annie_toggleHighlights(imgUrl)
{
	jQuery('.annie_highlightText').each(function(index) {
		var annie_style = jQuery(this).attr('highlight');
		
		if (annie_highlightShowing)
		{
			jQuery(this).removeClass(annie_style);
		} else {
			jQuery(this).addClass(annie_style);
		}
	});
	
	if (annie_highlightShowing)
	{
		annie_highlightShowing = false;
		jQuery('#annie_toggle_highlight').html('<img style="width: 14px; height: 14px;" src="' + imgUrl + '/annie/images/star_black.png" alt="Show Highlights" title="Show Highlights" />');
	} else {
		annie_highlightShowing = true;
		jQuery('#annie_toggle_highlight').html('<img style="width: 14px; height: 14px;" src="' + imgUrl + '/annie/images/star_green.png" alt="Hide Highlights" title="Hide Highlights" />');
	}
}

function annie_showHighlights()
{
	if (!jQuery('#annie_highlightTextBox').is(":visible"))
	{
		var annie_text = "";
		var highlightText = "";
		jQuery('.annie_highlightText').each(function(index) {
			highlightText = jQuery(this).html();
			var tippyFound = jQuery(":contains('Tippy')", this);
			annie_text = annie_text + highlightText + "<br /><br />";
		});
		annie_text = '<div id="annie_highlightTextBoxHeader">Highlighted Text</div>' + annie_text;
		
		jQuery('#annie_highlightTextBox').html(annie_text);
		
		// Create and pop up the overlay
		var windowHeight = jQuery(window).height();
		var windowWidth = jQuery(window).width();
		var annieOverlay = jQuery('<div id="annieOverlay">&nbsp;</div>');
		annieOverlay.height(windowHeight);
		annieOverlay.width(windowWidth);
		annieOverlay.appendTo('body');
		
		jQuery('#annie_highlightTextBox').css("position","fixed");
		jQuery('#annie_highlightTextBox').css("top", ( jQuery(window).height() - jQuery('#annie_highlightTextBox').height() ) / 2 + "px");
		jQuery('#annie_highlightTextBox').css("left", ( jQuery(window).width() - jQuery('#annie_highlightTextBox').width() ) / 2 + "px");
		jQuery('#annie_highlightTextBox').css("z-index", "1100");
		
		jQuery('#annie_highlightTextBox').fadeIn(200);
		annieOverlay.fadeIn(200);
	} else {
		annie_hideHighlights();
	}
}

function annie_hideHighlights()
{
	jQuery('#annie_highlightTextBox').fadeOut(200);
	jQuery('#annieOverlay').fadeOut(200, function() {
		jQuery('#annieOverlay').remove();
	});
}

function annie_toggleToolbox()
{
	var toolboxWidth = jQuery('#annie_toolbox').width();
	var toolboxToggleWidth = jQuery('#annie_toolbox_toggle').width();
	toolboxMove = toolboxWidth - toolboxToggleWidth;
	
	if (jQuery('#annie_toolbox').attr('showing') == 'full')
	{
		toolboxAdjust = "-=" + toolboxMove;
		jQuery('#annie_toolbox_toggle').html('&raquo;');
		jQuery('#annie_toolbox').attr('showing', 'part');
	} else {
		toolboxAdjust = "+=" + toolboxMove;
		jQuery('#annie_toolbox_toggle').html('&laquo;');
		jQuery('#annie_toolbox').attr('showing', 'full');
	}
	
	jQuery('#annie_toolbox').animate({ left: toolboxAdjust });
}