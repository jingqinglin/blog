/*!
 * docsify-plugin-flexible-alerts
 * v1.0.4
 * https://github.com/zanfab/docsify-plugin-flexible-alerts#readme
 * (c) 2019 Fabian Zankl
 * MIT license
 */
(function () {
    "use strict";
    function _typeof (obj) {
        if (typeof Symbol === "function" && typeof Symbol.iterator === "symbol") {
            _typeof = function (obj) {
                return typeof obj;
            };
        } else {
            _typeof = function (obj) {
                return obj && typeof Symbol === "function" && obj.constructor === Symbol && obj !== Symbol.prototype ? "symbol" : typeof obj;
            };
        }
        return _typeof(obj);
    }
    function styleInject (css, ref) {
        if (ref === void 0) ref = {};
        var insertAt = ref.insertAt;
        if (!css || typeof document === "undefined") {
            return;
        }
        var head = document.head || document.getElementsByTagName("head")[0];
        var style = document.createElement("style");
        style.type = "text/css";
        if (insertAt === "top") {
            if (head.firstChild) {
                head.insertBefore(style, head.firstChild);
            } else {
                head.appendChild(style);
            }
        } else {
            head.appendChild(style);
        }
        if (style.styleSheet) {
            style.styleSheet.cssText = css;
        } else {
            style.appendChild(document.createTextNode(css));
        }
    }
    var css = '@import url("https://cdn.jsdelivr.net/npm/@fortawesome/fontawesome-free/css/solid.css");@import url("https://cdn.jsdelivr.net/npm/@fortawesome/fontawesome-free/css/fontawesome.css");.alert{display:block;position:relative;word-wrap:break-word;word-break:break-word;padding:.75rem 1.25rem!important;margin-bottom:1rem!important}.alert>*{max-width:100%}.alert+.alert{margin-top:-.25rem!important}.alert:before{content:unset!important}.alert p{margin-top:.5rem;margin-bottom:.5rem}.alert i{margin-right:.5rem}.alert .title{font-weight:600;margin:0}.alert>:first-child{margin-top:0}.alert>:last-child{margin-bottom:0}.alert.callout{border:1px solid #eee;border-left-width:.25rem;border-radius:.25rem;background:#fff}.alert.callout.warning{border-left-color:#f0ad4e!important}.alert.callout.warning .title{color:#f0ad4e}.alert.callout.tip{border-left-color:#28a745!important}.alert.callout.tip .title{color:#28a745}.alert.callout.info{border-left-color:#17a2b8!important}.alert.callout.info .title{color:#17a2b8}.alert.callout.danger{border-left-color:#dc3545!important}.alert.callout.danger .title{color:#dc3545}.alert.flat{border-radius:.125rem;color:#383d41;background-color:#e2e3e5;border:1px solid #d6d8db}.alert.flat.info{color:#02587f;background-color:#cdeefd;border-color:#b8e7fc}.alert.flat.info .title{color:#01354d}.alert.flat.tip{color:#285b2a;background-color:#dbefdc;border-color:#cde9ce}.alert.flat.tip .title{color:#18381a}.alert.flat.warning{color:#852d12;background-color:#ffddd3;border-color:#ffd0c1}.alert.flat.warning .title{color:#581e0c}.alert.flat.danger{color:#7f231c;background-color:#fdd9d7;border-color:#fccac7}.alert.flat.danger .title{color:#551713}';
    styleInject(css);
    (function () {
        var CONFIG = {
            style: "callout",
            note: {
                label: "Note",
                icon: "fas fa-info-circle",
                className: "info"
            },
            tip: {
                label: "Tip",
                icon: "fas fa-lightbulb",
                className: "tip"
            },
            warning: {
                label: "Warning",
                icon: "fas fa-exclamation-triangle",
                className: "warning"
            },
            danger: {
                label: "Attention",
                icon: "fas fa-ban",
                className: "danger"
            }
        };
        function mergeObjects (obj1, obj2) {
            var level = arguments.length > 2 && arguments[2] !== undefined ? arguments[2] : 0;
            for (var property in obj2) {
                try {
                    if (obj2[property].constructor === Object && level < 1) {
                        obj1[property] = mergeObjects(obj1[property], obj2[property], level + 1);
                    } else {
                        obj1[property] = obj2[property];
                    }
                } catch (e) {
                    obj1[property] = obj2[property];
                }
            }
            return obj1;
        }
        var install = function install (hook, vm) {
            var options = mergeObjects(CONFIG, vm.config["flexible-alerts"] || vm.config.flexibleAlerts);
            var findSetting = function findAlertSetting (input, key, fallback, callback) {
                var match = (input || "").match(new RegExp("".concat(key, ":(([\\s\\w\\u00A0-\\uD7FF\\uF900-\\uFDCF\\uFDF0-\\uFFEF-]*))")));
                if (!match) {
                    return callback ? callback(fallback) : fallback;
                }
                return callback ? callback(match[1]) : match[1];
            };
            hook.afterEach(function (html, next) {
                var modifiedHtml = html.replace(/<\s*blockquote[^>]*>(?:<p>|[\S\n]*)?\[!(\w*)((?:\|[\w*:[\s\w\u00A0-\uD7FF\uF900-\uFDCF\uFDF0-\uFFEF-]*)*?)\]([\s\S]*?)(?:<\/p>)?<\s*\/\s*blockquote>/g, function (match, key, settings, value) {
                    var config = options[key.toLowerCase()];
                    if (!config) {
                        return match;
                    }
                    var style = findSetting(settings, "style", options.style);
                    var isIconVisible = findSetting(settings, "iconVisibility", "visible", function (value) {
                        return value !== "hidden";
                    });
                    var isLabelVisible = findSetting(settings, "labelVisibility", "visible", function (value) {
                        return value !== "hidden";
                    });
                    var label = findSetting(settings, "label", config.label);
                    var icon = findSetting(settings, "icon", config.icon);
                    var className = findSetting(settings, "className", config.className);
                    if (_typeof(label) === "object") {
                        var foundLabel = Object.keys(label).filter(function (key) {
                            return vm.route.path.indexOf(key) > -1;
                        });
                        if (foundLabel && foundLabel.length > 0) {
                            label = label[foundLabel[0]];
                        } else {
                            isLabelVisible = false;
                            isIconVisible = false;
                        }
                    }
                    var iconTag = '<i class="'.concat(icon, '"></i>');
                    return '<div class="alert '.concat(style, " ").concat(className, '">\n            <p class="title">\n                ').concat(isIconVisible ? iconTag : "", "\n                ").concat(isLabelVisible ? label : "", "\n            </p>\n            <p>").concat(value, "</p>\n          </div>");
                });
                next(modifiedHtml);
            });
        };
        window.$docsify = window.$docsify || {};
        window.$docsify.plugins = [].concat(install, window.$docsify.plugins);
    })();
})();
//# sourceMappingURL=docsify-plugin-flexible-alerts.js.map
