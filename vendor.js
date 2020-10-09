require(["gitbook"], function(gitbook) {
    gitbook.events.bind("start", function(e, config) {
    });

    // Notify pageview
    gitbook.events.bind("page.change", function() {
      docSetupIdeDownloadUrl();
      docSetupCopyright();
      docSetupIndexPage();
      docSetupDemoLink();
    });
});

function docSetupIdeDownloadUrl() {
    link_ide = $("#ide-download");
    if (link_ide != null) {
      if ("developer.flywizos.com" == document.domain) {
        link_ide.attr("href", "http://download.zkswe.com/ide/flythings-ide-win32-win32-x86-zkswe-setup.exe");
      } else if ("docs.flywizos.com" == document.domain) {
        link_ide.attr("href", "http://download.zkswe.com/ide/flythings-ide-win32-win32-x86-community-setup.exe");
      } else {
      }     
    }
}
function docSetupCopyright() {
    spancopyright = $("span.copyright").first();
    if (spancopyright != null) {
      if ("developer.flywizos.com" == document.domain) {
        spancopyright.html('Copyright &copy 2020 <a target="_blank" href="http://www.flywizos.com" > <b>MultiChannelLabs</b></a>');
      } else if ("docs.flywizos.com" == document.domain) {
      } else {
      }     
    }
}
function docSetupIndexPage() {
    customLink = $("a.custom-link").first();
    if (customLink != null) {
      customLink.attr("href", window.location.href.slice(0,window.location.href.length - window.location.pathname.length));
    }
}
function docSetupDemoLink() {
  if ("docs.flywizos.com" == document.domain) {
    $("li[data-path='demo_download.html']").first().remove();
    $("a[href^='demo_download.html']").each(
      function(){
        txt=$(this).text();
        $(this).replaceWith(txt);
      }
    );
  }
}
