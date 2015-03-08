# btjsb

A simple build-time javascript bundler, which allows you to split your javascript code in smaller parts, while outputting a single monolithic file to the client.

Example:

```javascript
(function(window, document, undefined) {
	"use strict";
	include('inc/feature.js');
	include('inc/more/stuff.js');
	alert('hi!');
})(window, document);
```

Will output something like:

```javascript
(function(window, document, undefined) {
        "use strict";
// src/main.js:3 includes src/inc/feature.js
// src/inc/feature.js:1 includes src/inc/feature-requirement.js
function requirement() {
        // do required things
}
// end of src/inc/feature-requirement.js, back to src/inc/feature.js:1
function feature() {
        requirement();
}

// end of src/inc/feature.js, back to src/main.js:3
// src/main.js:4 includes src/inc/more/stuff.js
function stuff() {
        // do some stuff
}
// end of src/inc/more/stuff.js, back to src/main.js:4
        alert('hi!');
})(window, document);
```

## Installing
Getting **btjsb** running is simple:

```bash
$ git clone https://github.com/alfred300p/btjsb; cd btjsb
$ make
$ sudo make install # installs to /usr/bin/btjsb
```

You can skip the third step and just run it locally.
