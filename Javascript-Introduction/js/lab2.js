dataFiltering(attractionData);

function dataFiltering(attraction_category) {
	var attracts = attraction_category;
	
	var sortByProperty = function (property) {
		return function (x, y) {
			return ((x[property] === y[property]) ? 0 : ((x[property] > y[property]) ? 1 : -1));
		};
	};

	
	attracts.sort(sortByProperty('Visitors'));
	
	let topFive = getTopFive(attracts);
	function getTopFive (attracts)
	{
		var a = [];
		for(let i = attracts.length-1; i > attracts.length-6; i--)
		{
			a.push(attracts[i]);
		}
		return a;
	}
	console.log(topFive);
	renderBarChart(topFive);

}

function dataManipulation()
{
	var attractions = attractionData;
	var attracts = [];
	let selectBox = document.querySelector("#attraction-category");
	let selectedValue = selectBox.options[selectBox.selectedIndex].value;
	console.log(selectedValue);
	if(selectedValue == "all")
	{
		
		for(let i = 0; i < attractions.length; i++)
		{
			
			attracts.push(attractions[i]);
			
		}
	}
	if(selectedValue == "Theme Park")
	{
		
		for(let i = 0; i < attractions.length; i++)
		{
			if(attractions[i].Category == "Theme Park")
			{
				attracts.push(attractions[i]);
			}
		}
	}
	if(selectedValue== "Water Park")
	{
		
		for(let i = 0; i < attractions.length; i++)
		{
			if(attractions[i].Category == "Water Park")
			{
				attracts.push(attractions[i]);
			}
		}
	}
	if(selectedValue == "Museum")
	{
		
		for(let i = 0; i < attractions.length; i++)
		{
			if(attractions[i].Category == "Museum")
			{
				attracts.push(attractions[i]);
			}
		}
	}
	dataFiltering(attracts);
		
}