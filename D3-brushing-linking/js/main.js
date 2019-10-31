import StackedAreaChart from './StackedAreaChart.js';
import Timeline from './Timeline.js';

// Will be used to the save the loaded JSON data
let yearData, categoryData;

// Date parser to convert strings to date objects
let parseDate = d3.timeParse("%Y");

// Variables for the visualization instances
// Activity I - Create a stacked area chart
let areachart = StackedAreaChart();
// Activity V - register for the category selection event
function handleClick(d,i){
	listeners.apply("selectCategory", this, [d.key,d.index]);
}
// Activity III - Create a timeline chart
let timeline = Timeline()
.on('brushed', onBrushRange);

// Will be used to the save filter variables
let filterCategory, filterRange;

// Start application by loading the data
Promise.all([ // load multiple files
	d3.csv('data/per_year.csv', d=>{
		d.Expenditures = parseFloat(d.Expenditures) * 1.481105 / 100;
		d.Year = parseDate(d.Year.toString());
		return d;
	}),
	d3.csv('data/per_category.csv', d=>{
		Object.keys(d).forEach(key=>{
			//console.log(key)
			//console.log(d[key])
			if (key != "Year") {
				d[key] = parseFloat(d[key]) * 1.481105 / 100;
			} else if(key == "Year") {
				d[key] = parseDate(d[key].toString());
			}
		})
		
		return d; 
	})
]).then(data=>{
	//console.log(data[0])
	//console.log(data[1])
	yearData = data[0];
	categoryData = data[1];

	// Activity I - Call the stacked area chart
	d3.select('#stacked-area-chart') // a container element
	.datum(categoryData) // specify data
	.call(areachart);
	// Activity III - Call the timeline chart
	d3.select('#timeline')
	.datum(yearData) // per year data
	.call(timeline);

})
// callback for selecting a category in the stack area chart
function onSelectCategory(d,i){
	filterCategory = filterCategory===d?null:d; // toggle the filter to go back to all categories
	let filtered = filterCategoryData(filterCategory, filterRange);
	d3.select('#stacked-area-chart')
		.datum(filtered)
		.call(areachart);
}
areachart = StackedAreaChart()
.on('selectCategory', onSelectCategory);
			
// callback for brushing on the timeline
function onBrushRange(dateRange) {
	filterRange = dateRange;
	let filtered = filterCategoryData(filterCategory, filterRange);
	d3.select('#stacked-area-chart')
		.datum(filtered)
		.call(areachart);
}


// check if a year is within the year range
function within(d, range){
	return d.getTime()>=range[0].getTime()&&d.getTime()<=range[1].getTime();
}

// filter category data based on a specific category (if any) and year range
function filterCategoryData(category, dateRange){
	let filtered = dateRange?categoryData.filter(d=>within(d.Year, dateRange)): categoryData;
	filtered = filtered.map(row=>{
		return category?{
			Year:row.Year,
			[category]:row[category]
		}:row;
	});
	return filtered;
}