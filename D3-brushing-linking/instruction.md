--- 

layout: default
title: lab6

---
# <img src="img/instruction/logo.png" width="30px"> CSCI339001 Visualization

# Lab 6



### Learning Objectives

- Know how to *link* multiple views with each other
- Understand the concept behind D3's brush component
- Understand the JS keyword *this* and the scope of execution
- Get a better understanding of *system design* and *code structure*


### Prerequisites

<!-- - You have read and **programmed** along with:
	- [http://www.cs171.org/2019/assets/material/cs171-lab6-reading.pdf](http://www.cs171.org/2019/assets/material/cs171-lab6-reading.pdf)
	- The four chapters about JS objects at [http://www.w3schools.com/js/js_object_definition.asp](http://www.w3schools.com/js/js_object_definition.asp) (repetition of JS objects with more examples)
	- *[Optional]* [Scope and *this* in JavaScript](https://software.intel.com/en-us/xdk/blog/javascript-this-that-and-the-other-thing) -->

- You have read Chapter 10 and 12 in Interactive Data Visualization for the Web.
- You have also read [Toward Reusable Charts](https://bost.ocks.org/mike/chart/) by Mike Bostock.
- Accept the lab assignment invitation from Github Classroom: 
	[https://classroom.github.com/a/UWBSZWZX](https://classroom.github.com/a/UWBSZWZX)



In the last weeks, you have learned the fundamentals of the JS library D3 and you have gained some implementation expertise during previous labs and homeworks. You should be comfortable with the major concepts and be able to implement common interactive charts with D3.

In this lab you will work on a new problem set. It is continuous, a bit longer than the usual activities, and it will give you a better understanding of *linked views* and *system design* using JS modules.

We will provide a template and many additional code snippets so that your main tasks will focus on coordinating multiple independent visualization modules. However, please make sure that you understand everything in this lab. It will very helpful for structuring your team projects.


## Data

**Purchases for Household Supplies in the UK**

In this lab you will work with a dataset that contains detailed annual statistics on family food and drink purchases in the UK 1974 and 2013.

The data is divided into two separate csv files: 

- ```data/per_year.csv``` contain the average weekly spending on food and drinks in pence (GBX) per person
- ```data/per_category.csv``` also contain the average weekly spending, but separated into 21 different *food* categories


The data is part of the annual *Family Food Report*, it is published through UK's open government platform *gov.uk* and is updated every year. However, the dataset is not completely accurate and there is a lack of data in some areas. For example, alcoholic and soft drink figures appear for the first time in 1992, but we can assume that people have consumed these products before.

*Source: [https://www.gov.uk/government/statistical-data-sets/family-food-datasets](https://www.gov.uk/government/statistical-data-sets/family-food-datasets)*


## Preview

In this lab, we will introduce how to design an advanced D3 project by coordinating multiple visualizations into two separate modules that are implemented in separate JS files.


After implementing all tasks your visualization should look like the one below.

![Lab 7 - Preview](img/instruction/lab6-preview.gif?raw=true "Lab 7 - Preview")

 The above chart is a a stacked area chart (called Focus) linked with a basic area chart at the bottom (Context). To avoid confusion, we will call the basic area chart "timeline" because it shows the full time period.

## Modular Structure

The provided template is structured as follows:

- **index.html** is the default file that appears when a user invokes your webpage. It should include a basic structure and placeholders for your visualizations. 
- **/js** contains the JS files for the visualization and external libraries (can be further separated if necessary)
- **/data** contains the data files
- **/css** contains the stylesheet files


In the **`js`** folder, you will find a separate Javascript file for each chart as below
```
js/
    main.js
    StackedAreaChart.js
    Timeline.js
    ...
```
If you look at the file for each chart, you will see the chart is defined as a function module exported using the ```export``` syntax:
```javascript
// StackedAreaChart.js
export default function StackedAreaChart() 
    ...
}
```

```javascript
// Timeline.js
export default function Timeline() 
    ...
}
```

To use the charts, we can simply import ```StackedAreaChart.js``` and ```Timeline.js``` at the top of the ```main.js``` file as below:

```javascript
// in main.js
import StackedAreaChart from './StackedAreaChart.js';
import Timeline from './Timeline.js';

```
In the ```main.js```, you will load data and create and coordinate these two visualizations.

In the ```index.html```, you only need to include the entry point to your project, which is in our case ```main.js```:
```html
<script src="js/d3.min.js"></script>
<script type="module" src="js/main.js"></script>
```
Please note that you still need to include ```d3.js``` before ```main.js``` and make sure to add the ```type="module"``` attribute to enable ```import``` and ```export``` syntax.


You should always try to split a complex problem into smaller, easier-to-tackle sub-problems (e.g., separate files). Each sub-problem will be solved independently and afterwards integrated into the final system.

**Visualizations should be organized and structured into individual reusable modules, each of which is defined in a separate file.** This will help your team distribute workload into separate files, and each member of your team will on each file without causing conflict between them.


## Visualization Module Primer

As the most forgiving language in the world, there are so many different ways to structure your visualization as an independent module. In this lab, we will follow the suggestion from *Mike Bostock*, the creator of D3. Please take a look at his article again here: [Toward Reusable Charts](https://bost.ocks.org/mike/chart/).

We will use a function and [closure](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Closures) to create a visualization module.

```javascript

export default function StackedAreaChart(){
	// define configuration variables
    let margin ={
		top: 40,
		left: 60,
		right: 0,
		bottom: 60
	};
	let width = 800;
	let height = 400;
	...
	// chart function
	function chart(selection){
        selection.each(function(data){
            // draw chart into the selection based on the data
        })
    }
	chart.width = function(value) {
        if (!arguments.length) return width;
        width = value;
        return chart;
    };

    chart.height = function(value) {
        if (!arguments.length) return height;
        height = value;
        return chart;
    };
    ...
    return chart;
}
```
The structure is similar to classes. The configuration variables play a role like private variables that are bound to the ```chart``` function and can be exposed through separate getter-setter functions (e.g., ```chart.width()```). This is why people call it a closure. Those variables are closed from outside but available for inner functions. The closure is an advanced concept in Javascript. It's okay if you don't fully understand it. 


The ``` chart``` function is like a class object. In Javascript, a function is an object, so we can add properties and methods within.

To enable method chaining like this,

 ```javascript
 let areaChart = StackedAreaChart()
    .width(700)
    .height(400);
 ```
 we return the chart object itself in the getter-setter methods. To retrieve the height or width, you can simply call the method without the arguments: 
 
 ```javascript
 areaChart.width()
 ```

 Implementing charts as closures with getter-setter methods enables the elegant method chaining, following the same pattern as other D3 objects including scales and axes (e.g., ```scaleLinear().domain(...).range(...)```).

In order to render the chart, we still need to specify a container DOM element and data. We will leverage the D3 selection to specify the element and the data, again through method chaining.

```javascript
d3.select('#stacked-area-chart') // select a container element
    .datum(categoryData) // specify data
    .call(areachart);
 ```

 By separating the container element and data, your chart component becomes much more reusable. You can easily move the chart across different elements and update the data on demand without worrying about explicitly unbinding and rebinding. 

In the ```chart()``` function above, you will have access to the element and data that you can use to render the chart:
```javascript
export default function StackedAreaChart(){
    ...
    function chart(selection){ 
        selection.each(function(data){
        // data is the data and `this` is the DOM node
        
        // d3.select(this) to use d3 functions within
        
        // place your chart code here
       
    }
}
```

The selected DOM element will be available using the ```this``` keyword. ```this``` is not a D3 selection, so ```this.attr()``` will not work. You will have to *select* the element first using ```d3.select(this)```. 

You should not use an arrow function here. If you do this:
```javascript
    function chart(selection){ 
        selection.each(data=>{
            // 'this' here is not the container DOM element you want
        });

```
`this` will be different because an arrow function does not bind its own `this`. It will use its parent's context as `this`. You don't have to understand this difference but you can find more details here: [Javascript ES6 — Arrow Functions and Lexical `this`](https://hackernoon.com/javascript-es6-arrow-functions-and-lexical-this-f2a3e2a5e8c4).



## StackAreaChart

### Activity I - Create an instance of the stacked area chart


1. **Check out the ```StackedAreaChart.js```**

    We provide a boilerplate for the implementation of the stacked area chart. In the ```chart(selection)``` function you will see the code that creates an internal structure (groups and axes) of the chart based on the following code.
 

    ```javascript
    // StackedAreaChart.js
    function chart(selection){ 
        // ---- Init the internal structure only once -----
        let svg = d3.select(this).select('svg').selectAll('svg')
            .data([data]);

        let svgEnter = svg.enter().append('svg');
        // Placeholder for visualization Elements
        let gEnter = svgEnter.append('g');
        // Axes placeholders
        gEnter.append("g")
            .attr("class", "x-axis axis")
        gEnter.append("g")
            .attr("class", "y-axis axis");

        // ------------------------------------------------
        ...
    }
    ```

    Please note that the above code initializes that the internal structure only once using the enter selection. It cleverly uses ```.selectAll('svg').data([data])``` to perform the initialization only when there is no svg in the container element.

    In the data loading callback in `main.js`, you first select the HTML container element with id of `#stacked-area-chart`, specify the data, and call the chart like this.
    ```javascript
    // main.js
    d3.select('#stacked-area-chart')
        .datum(categoryData)// only single item, so datum not data
        .call(stackChart);
    ```

2. **Create an instance of ```StackedAreaChart``` in ```main.js```**

    As we discussed before, you can instantiate the chart in ```main.js`` in the following way:
    
    ```javascript
    import StackedAreaChart from './StackedAreaChart.js';
    ...

    // Activity I: Instantiate StackedAreaChart here
    let stackChart = StackedAreaChart();
    ```
    This does not do anything for now. You need to call the chart by specifying the selection and data. 

3. **Call the chart after data is loaded**

    We already provide a data loading script that loads both ```per_category.csv``` and ```per_year.csv``` simultaneously:
    ```javascript

    Promise.all([ // load multiple files
        d3.csv('data/per_year.csv', d=>{
            // type conversion ...
        }),
        d3.csv('data/per_category.csv', d=>{
            // type conversion ...
        })
    ]).then(data=>{
        yearData = data[0];
        categoryData = data[1];
        console.log(yearData, categoryData);

        //Call the stackChart on a HTML container selection and per category data
    })

    ```

    The way you call your chart follows the same syntax as other D3 functions. You first need to select the chart container (#stacked-area-chart), specify the data, and *call* ```stackChart``` through method chaining.
    ```javascript
    d3.select('#stacked-area-chart') // a container element
    .datum(categoryData) // specify data
    .call(areachart);
    ```

    Open the webpage in your browser and inspect the HTML. You will see the internal structure of the stacked chart is initialized as below:

    ![Lab 7 - Stack Chart Internal Structure](img/instruction/stack-chart-internal-structure.png?raw=true "Lab 7 - Stack Chart Internal Structure")


----

### Stack Shape

As you have seen in the preview at the beginning of this lab, you have to create a stacked area chart to visualize the different categories of UK's household expenditures. Instead of calculating the coordinates of these layers manually you can use [*d3.stack()*](https://github.com/d3/d3-shape/blob/v1.3.5/README.md#stack) to generate a baseline value for each datum, so you can "stack" layers of data on top of each other.

And as a reminder from the previous lab: *The D3 shape methods have no direct visual output. They take data that you provide and re-map or otherwise transform it, thereby generating new data that is more convenient for a specific task.*

*Example:*

```javascript
// Example data
var data = [
                {
                    "Milk": 10, "Water": 4, "Year": 2015
                },
                {
                    "Milk": 12, "Water": 6, "Year": 2016
                },
                {
                    "Milk": 11, "Water": 7, "Year": 2017
                }
            ];

// Initialize shape function specifying keys
var stack = d3.stack()
	.keys(["Milk", "Water"]);

// Call shape function on the dataset
var stackedData = stack(data);

console.log(stackedData);
```

Have a look at the console output. The resulting stacked data is now an array with two values, with each value an array itself corresponding to each category: "Milk", and "Water". Each entry in a category array provides two numerical values and the associated data object (```series[0][0].data```). The numerical values correspond to the *baseline* value, and the *topline* values respectively. For example, the first entry for "Milk" is ```series[0][0]``` where ```series[0][0][0]``` is the baseline and ```series[0][0][1]``` is the topline. Notice that the baseline value is equal to the sum of all the y values in the preceding categories. The category *"Milk"* is our first category and starts at the bottom, which means that the baseline values are zero. 


### Stacked Area

To stack these categories visually, we can create *stacked bar charts* or *stacked area charts*. In this lab you will create a stacked area chart. But it should be easy to adopt the workflow to a bar chart.

[```d3.area```](https://github.com/d3/d3-shape/blob/master/README.md#areas) provides a convenient function for generating a area path. An area is defined by two bounding lines. For the stacked area chart, the two lines share the same x-values (x = x0 = x1), differing only in y-value (y0 and y1).

```javascript
// Basic: a single area
var areaBasic = d3.area()
	.curve(d3.curveCardinal)
	.x(function(d) { return x(d.data.Year); })
	.y0(height) // baseline fixed at the bottom
	.y1(function(d) { return y(d[1]-d[0]); });

// Extended: stacked area
var areaExtended = d3.area()
	.curve(d3.curveCardinal)
	.x(function(d) { return x(d.data.Year); })
	.y0(function(d) { return y(d[0]); }) // baseline variable
	.y1(function(d) { return y(d[1]); });
```

*The [d3.curveCardinal](https://github.com/d3/d3-shape/blob/master/README.md#curveCardinal) interpolation curve is optional and can be used to create smooth shapes.*

----


### Activity II - Create a stacked area chart

Now we are going to define a stack area chart in ```StackedAreaChart.js``` by following the steps below. 


1. **Define Margins**

    We will start by following the margin convention, defining a canvas size for drawing:
    ```javascript
    svg.attr("width", width)
            .attr("height", height)
        
    let g = svg.select("g")
        .attr("transform", "translate(" + margin.left + "," + margin.top + ")");
    ```

    This code comes right below the initialization of the internal structure so that ```svg``` is available for us. Everytime you call the chart, this code will be run and update the canvas size, if you have changed the width and height variables. 

2. **Compute Stack Layout**
	You will need the list of categories to serve as keys for the stack function. We provide the following code that extract categories and create a stack layout.

    ```javascript
        let dataCategories = data.length>0?Object.keys(data[0]).filter(d=>d!=="Year"):[];
            
        // Initialize stack layout
        stack = d3.stack()
            .keys(dataCategories);
            
        // Stack data
        stackedData = stack(data);
    ```

3. **Define X, Y, and Color Scales**

    We already declared scales in the configuration code at the top of ```StackedAreaChart.js```:

    ```javascript
    let x = d3.scaleTime();
	let y = d3.scaleLinear();
	let color = d3.scaleOrdinal(d3.schemeCategory10);
    ```

    You just need to define the ranges and domains of the scales when the chart function is called. The reason we are doing this on demand is to react to potential changes in both data and canvas size, making the chart reusable for new data and new display size.

    ```javascript
    x.range([0, width - margin.left - margin.right])
    .domain(d3.extent(data, d=>d.Year));
    
    y.range([height - margin.top - margin.bottom, 0])
    .domain([0,d3.max(stackedData, d => d3.max(d, d => d[1]))]);
    
    color.domain(dataCategories);
    ```

    The x-scale will use the min and max of the year dimension as its domain, while the y-scale will compute the domain based on the min and max of the total stack of all categories. The domain of the color scale is the list of categories.

4. **Define Area Path Generator**

    To generate layers in the stacked area chart, you can use ```d3.area()``` as we discussed above. This will use the precomputed ```stackedData``` to generate the top and bottom y-positions of the area layer, while x-position is fixed based on each year. 
	
	```javascript
    area = d3.area()
    .curve(d3.curveCardinal)
    .x(d=>x(d.data.Year))
    .y0(d=>y(d[0]))
    .y1(d=>y(d[1]));
	```

5. **Draw areas**

    Now we have everything to draw actual stacked areas. We will again use the enter-update-exit pattern to make it agnostic for future data changes.
    ```javascript
    // Draw the layers
    let categories = g.selectAll(".area")
        .data(stackedData);
    
    categories.enter().append("path")
        .attr("class", "area")
        .merge(categories)
        .style("fill", (d,i)=>color(dataCategories[i])) // assign color
        .attr("d", d=>area(d)); // delegate area path generation
    
    categories.exit().remove();
    ```
6. **Draw Axes**
    Finally, to provide a visual guide, you need to generate axes. We already defined axes functions in the ```StackedAreaChart.js``` for you.
    ```javascript
    let yAxis = d3.axisLeft().scale(y);
	let xAxis = d3.axisBottom().scale(x);;
    ```
    You just need to call the axis functions using the axes containers as their context elements.
    ```javascript
    g.select(".x-axis")
        .attr("transform", "translate(0," + (height-margin.top-margin.bottom) + ")");
        .call(xAxis);
    g.select(".y-axis").call(yAxis);    
    ```

    Once you finish all aforementioned steps, you will be able to see a stacked area chart on the browser.

    If nothing appears, then you may be working on the empty update selection. Try merging with the enter selection. The update selection is initially empty (you should know why it's empty on the first call!):
    ```javascript
    svg = svg.merge(svgEnter);
    ```


---

### Focus+Context via Brushing

In the next task, you will extend the stacked area chart with a timeline chart (a basic area chart; see *Preview*), to give the user the possibility to zoom and to select a specific time range. 

#### Focus+Context

- The stacked area chart should show selected regions in greater detail (*focus*)
- The timeline chart preserves a global view at reduced detail without layers (*context*)

*This technique allows us to show the user detailed information linked with an overview (context) simultaneously.*

#### Brushing & Linking

The idea of *brushing* is to allow the user to select a subset of data interactively. In combination with *linking* - changes are automatically reflected in *linked* visualizations - you can get the desired focus+context visualization.

![Focus + Context](img/instruction/focus-context.gif?raw=true "Focus + Context")


#### Brushing with D3

D3 Wiki: [https://github.com/d3/d3-brush/blob/master/README.md](https://github.com/d3/d3-brush/blob/master/README.md)

There are three types of brushes in D3 for brushing along the x, y dimensions, or both: d3.brushX, d3.brushY, and d3.brush. Each brush defines a selection in screen coordinates. The brushable area is specified via ```brush.extent()``` in pixel coordinates (typically the size of your visualization).

The property **```on```** must be used to set an event listener, whereby you can choose between three different events:

- ```brushstart``` - on mousedown
- ```brush``` - on mousemove, if the brush extent has changed
- ```brushend``` - on mouseup

```javascript
// Initialize time scale (x-axis)
let xScale = d3.scaleTime()
	.range([0, width])
    .domain(d3.extent(data, function(d) { return d.Year; }));
    
// Initialize brush component
let brush = d3.brushX()
    .extent([[0, 0], [width, height]]) // brushable area
    .on("brush", brushed);
    
```

We can react to the *event* and update the linked visualizations in a separate function. When the brush event occurs and your callback is called, D3 exposes current brush selection in [d3.event](https://github.com/d3/d3-brush#brush-events) (global variable) that has the following fields:

* **target** - the associated brush behavior.
* **type** - the string “start”, “brush” or “end”; see brush.on.
* **selection** - the current brush selection.
* **sourceEvent** - the underlying input event, such as mousemove or touchmove.

You are mostly interested in the ```selection``` to derive a data range to filter the linked visualizations. The ```selection``` is defined in pixel coords, so you need to convert it into the data domain using the [```invert```](https://github.com/d3/d3-scale#continuous_invert).

```javascript
function brushed() {
    
    // Get the extent of the current brush
    let pixelRange = d3.event.selection;
	
    // Convert the extent into the corresponding domain values
    let dataRange = d3.event.selection.map(x.invert);// or .map(d=>x.invert(d))
	
	// Update focus chart (detailed information)
	...
}
```

In order to render the brush, you need to apply the brush to a specific SVG group element as below. Internally, D3 will attach event listeners for brushing and also generate SVG elements to visualize the brushed area (see more details [here](https://github.com/d3/d3-brush#_brush)). This is similar to the generation of axes where you call your axis function on a SVG group element.

```javascript
// Append brush component to a SVG group
svg.append("g")
    .attr("class", "x brush")// allows to select the brush in CSS to customize styles
    .call(brush)
```

---

#### Activity III - Implement Focus+Context

*In the next activity you will have to implement a second chart (```Timeline.js```) with an interactive brushing component. Most of the parts are already complete but you have to connect the components to each other by following the steps below.*

1. **Create an instace of ```Timeline``` in ```main.js```**


	
	You can find the implementation of the timeline in ```js/Timeline.js```. The self-contained component follows the same approach for reusable charts.

	→ Open ```Timeline.js``` and get an overview of the implementation. It is much shorter than the stacked area chart because the area path and the axis is static.
	
	→ Create an instance of ```Timeline``` in ```main.js```.
    ```javascript
    // main.js
    let timeline = Timeline();
    ``` 


2. **Call the chart after the data is loaded.**

    The timeline will use the total year data not the per category data. You need to call the timeline chart on the selection of the HTML element with ID of "timeline".
    ```javascript
    // main.js
	d3.select('#timeline')
		.datum(yearData) // per year data
        .call(timeline);
    ```
    
	↻ Reload the webpage in your browser. If you have created the instance correctly you should see the timeline below your stacked area chart.

3. **Implement the brushing in ```Timeline.js```**

	You have to extend the timeline and implement the described focus+context approach for the visualization. We already created a brush variable at the top of ```Timeline.js```.

    ```javascript
    // Timeline.js
    brush = d3.brushX();
    ```

    You need to define the extent of the brush area using the ```innerWidth``` and ```innerHeight``` (defined in the template following the margin convention), and add a event listener for brushing. We already defined a brush event listener for you (i.e., ```handleBrush```).

    ```javascript
    // Timeline.js
    brush.extent([[0, 0], [innerWidth, innerHeight]])
        .on("brush", handleBrush);
    ```

    Also, you need to render the brush on a SVG group element:

    ```javascript
    // Timeline.js
    g.select('.brush').call(brush)
    ```

    Now you have a brushable timeline chart but it does not coordinate with the stacked area chart yet.

    
4. **Connecting ```Timeline.js``` and ```StackedAreaChart.js``` in ```main.js```**

    Currently the timeline and stacked area chart are separated into two independent files. How can we help them communicate each other? 

    To address this issue, we will use [```d3-dispatch```](https://github.com/d3/d3-dispatch) to allow each module to define custom events on which other modules can listen. You create a dispatch variable using ```d3.dispatch``` by passing a name for the event (multiple names possible separated by commas). Define the listeners variable at the top of the ```Timeline.js```:
    ```javascript
    // Timeline.js
    let listeners = d3.dispatch('brushed'); // 'brushed' is the name of our custom event
    ```

    Now, you need to enable external modules to register on the brush event, by exposing a public function as below:

    ```javascript
    // Timeline.js
	chart.on = function() {// allow users to register for your custom events 
        var value = listeners.on.apply(listeners, arguments);
        return value === listeners ? chart : value;
    };
    ```

    In ```main.js``` where you "use" the timeline chart, you can register a callback like this:
    ```javascript
    // main.js
    let timeline = Timeline()
        .on('brushed', onBrushRange); // register your custom callback, brushed
    
    ... 
    function onBrushRange(yearRange) {
        filterRange = yearRange;
        // filter data based on the brush range
        let filtered = filterCategoryData(filterCategory, filterRange); 

        // Redraw Stacked Area Chart
        d3.select('#stacked-area-chart')
            .datum(filtered)
            .call(areachart);
    }
    ```

    But, you may wonder who is calling the registered callback. In fact, you are in charge of calling it as it is your custom event. When the brushing occurs, your ```handleBrush``` function will be called. In this function, you need to call the registered callback as below:
    ```javascript
    // Timeline.js
    function handleBrush(){
        listeners.apply('brushed', this, [d3.event.selection.map(x.invert), d3.event.selection]); 
    }
    ```
    ```listerners``` is your D3 dispatch variable that has a function called [```apply```](https://github.com/d3/d3-dispatch#dispatch_apply). You need to pass the name of the event (this will tell D3 which callback to call when multiple custom events exist), the second argument is going to be the context of the callback (`this`) and the last array is going to be the parameters to be sent to the callback. 
    
    In this example, we are sending both data range (```d3.event.selection.map(x.invert)```) and pixel brush range (```d3.event.selection```). In the `onBrushRange` function, we are only using the first argument which is the data range.

    The following figure shows the schematic diagram for the dispatch workflow:
    
    ![Dispatch](img/instruction/dispatch-flow.png?raw=true "Dispatch")


	↻ Reload the webpage in your browser. You should be able to choose a specific time period in the timeline (context) and the stacked area chart (focus) will automatically zoom in and will show the details for the selected years.
	
---

#### Activity IV - Implement basic tooltips

*Currently it is not possible to identify layers and to get detailed information for a specific year. All of this would require an advanced tooltip solution.*

You will implement a lightweight version of these tooltips which should help the user to identify just the category names.

1. **Append a tooltip placeholder**

	Open ```StackedAreaChart.js``` and append an empty SVG text element. This element should be created only once. It should be used as a placeholder for the category names and should get updated every time the user hovers over a layer.
	
	Feel free to choose proper coordinates. In the preview the label is positioned in the top left corner of the stacked area chart.

    ```javascript
    // Example tooltip placeholder
    gEnter.append("text") // use gEnter to create this only once!
        .attr("class", "focus")
        .attr("x", 20)
        .attr("y", 0)
        .attr("dy", ".35em");	
    ```
	
2. **Update the tooltip**
    To update the text, you should first select the tooltip placeholder:
    ```javascript
    tooltip = g.select('.focus');
    ```
    
	And then, attach ```mouseover``` and ```mouseout``` listeners to the *SVG area paths* (layers of stacked area chart) and update the ```text``` property of the tooltip-element every time the user hovers over it.

    ```javascript
    .on("mouseover", (d,i)=>tooltip.text(excerpt(dataCategories[i], 100)))
    .on("mouseout", d=>tooltip.text(""));
    ```

    Sometimes, the tooltip text can be very long so we provide a helper function, ```excerpt``` to abbreviate the text given the character limit. Please import this function from ```excerpt.js``` at the top of ```StackedAreaChart.js``` and use it as above.

---

#### Activity V - Show details for a specific layer

Due to the stacked layout it is sometimes difficult to see the exact evolution of a specific layer. An extension which allows the user to click on a category in order to see the details would solve this problem.

![Layer Details](img/instruction/layer-details.gif?raw=true "Layer Details")

Remember, our visualization is module is independent of the data. ```main.js``` will be responsible for filtering the data, so we only need to pass the selected category from ```StackedAreaChart.js```. 

We will address this issue by defining a custom event and dispatching the event to ```main.js``` whenver a user click a specific category. 

1. Define a custom event and allow ```main.js``` to register a callback for the event
    ```javascript
    // StackedAreaChart.js

    let listeners = d3.dispatch('selectCategory');

    ...

    chart.on = function() {
        var value = listeners.on.apply(listeners, arguments);
        return value === listeners ? chart : value;
    };

    ```

2. Disatch the event when a user click a specific category in the stack area chart

    First you need to add a click listener to the layers of the stack, similar to the tooltip implementation:
    ```javascript
    // StackedAreaChart.js
    ...
    .on("click", handleClick)
    ...
    ```
    In the ```handleClick``` listener, you will get the data bound to the clicked area including the category name (d.key) and stack order (d.index). You will call registered callbacks by sending this information, similar to how we dispatched the brushing event in ```Timeline.js```.

    ```javascript
    // main.js
	function handleClick(d,i){
		listeners.apply("selectCategory", this, [d.key,d.index]);
	}
    ```
    In ```main.js```, you will need to register a callback for ```selectCategory``` event:
    ```javascript
    // StackedAreaChart.js
    let areachart = StackedAreaChart()
    .on('selectCategory', onSelectCategory);
    ```
    And filter the category data to only show the specific category:
    ```javascript
    // main.js
    function onSelectCategory(d,i){
        filterCategory = filterCategory===d? null: d; // toggle the filter	
        let filtered = filterCategoryData(filterCategory, filterRange);
        d3.select('#stacked-area-chart')
            .datum(filtered)
            .call(areachart);
        }
    ```


Great job, you now have a focus-and-context visualization that even allows you to get details on individually selected categories!

-----

### Submission of lab (activity I - V)

Congratulations, you have now completed the activities of Lab 6!

Please submit the **Github Pages url**, as well as **the link to the repository**, to Canvas.

Thanks!

-----

&nbsp;

**Resources**

- p. 273-281 in *D3 - Interactive Data Visualization for the Web* by Scott Murray
- [http://javascriptplayground.com/blog/2012/04/javascript-variable-scope-this/](http://javascriptplayground.com/blog/2012/04/javascript-variable-scope-this/)
- [https://developer.mozilla.org/en-US/docs/Web/JavaScript/Introduction_to_Object-Oriented_JavaScript](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Introduction_to_Object-Oriented_JavaScript)
- [http://www.w3schools.com/js/default.asp](http://www.w3schools.com/js/default.asp)
