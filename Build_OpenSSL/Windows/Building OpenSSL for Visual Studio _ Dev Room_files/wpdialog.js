(function(a){a.ui.dialog.prototype.options.closeOnEscape=false;a.widget("wp.wpdialog",a.ui.dialog,{widgetEventPrefix:"wpdialog",open:function(){var b;if(tinyMCEPopup&&typeof tinyMCE!="undefined"&&(b=tinyMCE.activeEditor)&&!b.isHidden()){tinyMCEPopup.init()}if(this.isOpen()||false===this._trigger("beforeOpen")){return}this._super();this.element.focus();this._trigger("refresh")}})})(jQuery);