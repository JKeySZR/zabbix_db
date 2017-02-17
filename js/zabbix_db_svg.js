
jQuery(document).ready(function ($) {
    alert('hot dog flavored water');
});

(function ($) {
    Drupal.behaviors.doSomething = {
        attach: function (context, settings) {
            $(function () {
                // Code here is executed when the DOM is loaded.
                alert('gav gav');
            });
        }
    }
})(jQuery);

(function ($) {
    Drupal.behaviors.zbx_connect_status = {
        attach: function (context, settings) {
            var a = document.getElementById("svg_connect");
            var svgDoc = a.contentDocument;
            var svg_test = svgDoc.getElementById("g191");
            svg_test.setAttribute("fill", "green");
        }
    };
})(jQuery);