google.load('visualization', '1', {packages: ['corechart']});
google.setOnLoadCallback(drawVisualization);

function drawVisualization() {
  // Create and populate the data table.
//  var data = new google.visualization.DataTable();
//  data.addColumn('string', 'Year');
//  data.addColumn('number', 'Sales');
//  data.addColumn({type: 'string', role: 'tooltip'});
//  data.addColumn('number', 'Expenses');
//  data.addColumn({type: 'string', role: 'tooltip'});
//  data.addRows([
//    ['2004', 1000, '1M$ sales in 2004', 400,  '$0.4M expenses in 2004'],
//    ['2005', 1170, '1.17M$ sales in 2005', 460, '$0.46M expenses in 2005'],
//    ['2006', 660,  '.66$ sales in 2006', 1120, '$1.12M expenses in 2006'],
//    ['2007', 1030, '1.03M$ sales in 2007', 540, '$0.54M expenses in 2007']
//  ]);
  var data = new google.visualization.DataTable();
  data.addColumn('string', 'workflow status');
  data.addColumn('number', 'start');
  data.addColumn({type: 'string', role: 'tooltip'});
  data.addColumn('number', 'ongoing');
  data.addColumn({type: 'string', role: 'tooltip'});
  data.addColumn('number', 'completed');
  data.addColumn({type: 'string', role: 'tooltip'});
  data.addRows([
                ['client 1', 2, 'start', 10, 'ongoing', 4, 'completed'],
                ['client 2', 4, 'start', 3, 'ongoing', 6, 'completed'],
                ]);
  
  // Create and draw the visualization.
  new google.visualization.ColumnChart(document.getElementById('visualization')).
  draw(data,
       {title:"Yearly Coffee Consumption by Country",
        isStacked: true,
        width:600, height:400,
        vAxis: {title: "number or projects"},
        hAxis: {title: "Clients"}}
      );
}