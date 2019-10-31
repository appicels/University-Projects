export default function Timeline(){
  // default size
let margin ={top: 0, right: 0, bottom: 30, left: 60};
let width = 800;
let height = 100;
let listeners = d3.dispatch('brushed');

// Scales and axes
let x = d3.scaleTime(),
  y = d3.scaleLinear(),
  xAxis = d3.axisBottom()
    .scale(x),
  area = d3.area(),
  brush = d3.brushX();
 
  
  // Activity III  create a new dispatch with a custom event 
  chart.on = function() {// allow users to register for your custom events 
    var value = listeners.on.apply(listeners, arguments);
    return value === listeners ? chart : value;
};
  
function chart(selection){
  selection.each(function(data){
    let innerWidth = width  - margin.left - margin.right; // margin convention
    let innerHeight =  height - margin.top - margin.bottom;

    // Initialize svg only if there is no svg within
    let svg = d3.select(this).selectAll('svg')
    .data([data]);

    // Initialize the internal structure only once
    let svgEnter = svg.enter().append('svg');
    let gEnter = svgEnter.append('g');

    gEnter.append("path");// path container (order matters)
    gEnter.append("g").attr("class", "x-axis axis"); // x-axis container
    gEnter.append("g").attr("class", "x brush");// brush container
    

    // Update canvas sizes
    svg = svg.merge(svgEnter);
    svg.attr("width", width)
      .attr("height", height)

    let g = svg.select("g")
      .attr("transform", "translate(" + margin.left + "," + margin.top + ")");
    
    x.range([0, innerWidth])
    .domain(d3.extent(data, d=>d.Year));

    y.range([innerHeight, 0])
      .domain([0, d3.max(data, d=>d.Expenditures)]);
    
    // SVG area path generator
    area.x(function(d) { return x(d.Year); })
      .y0(innerHeight)
      .y1(function(d) { return y(d.Expenditures); });

    // Draw area by using the path generator
    g.select('path')
      .datum(data)
      .join('path')
      .attr("fill", "#ccc")
      .attr("d", area);

    // Activity III - Set the brush extent, brush event listener, and render the brush
    brush.extent([[0, 0], [innerWidth, innerHeight]])
    .on("brush", handleBrush);
    g.select('.brush').call(brush)

    // Append x-axis
    g.select('.x-axis')
      .attr("transform", "translate(0," + innerHeight + ")")
      .call(xAxis);

  });
}

// Activity III  define 'on' function to enable external modules to register callbacks for the custom event
  // allow users to register for your custom events 

function handleBrush(){
  // Activity III  - call registered callbacks and send the brush filter information
  listeners.apply('brushed', this, [d3.event.selection.map(x.invert), d3.event.selection]); 
}

return chart;

}

