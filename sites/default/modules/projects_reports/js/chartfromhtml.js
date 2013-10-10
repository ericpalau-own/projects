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
                ['client 3', 3, 'start', 4, 'ongoing', 5, 'completed'],
                ['client 4', 4, 'start', 3, 'ongoing', 9, 'completed'],
                ['client 5', 5, 'start', 7, 'ongoing', 10, 'completed'],
                ['client 6', 7, 'start', 8, 'ongoing', 1, 'completed'],
                ['client 7', 12, 'start', 1, 'ongoing', 2, 'completed'],
                ['client 8', 1, 'start', 2, 'ongoing', 4, 'completed'],
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

/*
google.load('visualization', '1', {packages: ['corechart']});google.setOnLoadCallback(drawVisualization);function drawVisualization() {
  var data = new google.visualization.DataTable();
  data.addColumn('string', 'workflow status');
  data.addColumn('number', 'start');data.addColumn({type: 'string', role: 'tooltip'});data.addColumn('number', 'intercomms');data.addColumn({type: 'string', role: 'tooltip'});data.addColumn('number', 'on going');data.addColumn({type: 'string', role: 'tooltip'});data.addColumn('number', 'blocked');data.addColumn({type: 'string', role: 'tooltip'});data.addColumn('number', 'delayed');data.addColumn({type: 'string', role: 'tooltip'});data.addColumn('number', 'completed');data.addColumn({type: 'string', role: 'tooltip'});data.addRows([[Aetos Security Management Private Limited,13,Client Aetos Security Management Private Limited: 13 projects in start status.,1,Client Aetos Security Management Private Limited: 1 projects in intercomms status.,1,Client Aetos Security Management Private Limited: 1 projects in on going status.,0,Client Aetos Security Management Private Limited: 0 projects in blocked status.,0,Client Aetos Security Management Private Limited: 0 projects in delayed status.,0,Client Aetos Security Management Private Limited: 0 projects in completed status.],[AIBI International,2,Client AIBI International: 2 projects in start status.,0,Client AIBI International: 0 projects in intercomms status.,0,Client AIBI International: 0 projects in on going status.,0,Client AIBI International: 0 projects in blocked status.,0,Client AIBI International: 0 projects in delayed status.,0,Client AIBI International: 0 projects in completed status.],[Capital Dynamics (S) Pte Ltd,1,Client Capital Dynamics (S) Pte Ltd: 1 projects in start status.,0,Client Capital Dynamics (S) Pte Ltd: 0 projects in intercomms status.,0,Client Capital Dynamics (S) Pte Ltd: 0 projects in on going status.,0,Client Capital Dynamics (S) Pte Ltd: 0 projects in blocked status.,0,Client Capital Dynamics (S) Pte Ltd: 0 projects in delayed status.,0,Client Capital Dynamics (S) Pte Ltd: 0 projects in completed status.],[Chevron,2,Client Chevron: 2 projects in start status.,0,Client Chevron: 0 projects in intercomms status.,0,Client Chevron: 0 projects in on going status.,0,Client Chevron: 0 projects in blocked status.,0,Client Chevron: 0 projects in delayed status.,0,Client Chevron: 0 projects in completed status.],[Clouet Trading Pte. Ltd.,0,Client Clouet Trading Pte. Ltd.: 0 projects in start status.,0,Client Clouet Trading Pte. Ltd.: 0 projects in intercomms status.,0,Client Clouet Trading Pte. Ltd.: 0 projects in on going status.,0,Client Clouet Trading Pte. Ltd.: 0 projects in blocked status.,0,Client Clouet Trading Pte. Ltd.: 0 projects in delayed status.,0,Client Clouet Trading Pte. Ltd.: 0 projects in completed status.],[DBS Bank Limited,0,Client DBS Bank Limited: 0 projects in start status.,0,Client DBS Bank Limited: 0 projects in intercomms status.,0,Client DBS Bank Limited: 0 projects in on going status.,0,Client DBS Bank Limited: 0 projects in blocked status.,0,Client DBS Bank Limited: 0 projects in delayed status.,0,Client DBS Bank Limited: 0 projects in completed status.],[Exxon Mobil,3,Client Exxon Mobil: 3 projects in start status.,0,Client Exxon Mobil: 0 projects in intercomms status.,0,Client Exxon Mobil: 0 projects in on going status.,0,Client Exxon Mobil: 0 projects in blocked status.,0,Client Exxon Mobil: 0 projects in delayed status.,0,Client Exxon Mobil: 0 projects in completed status.],[Flextronics,0,Client Flextronics: 0 projects in start status.,0,Client Flextronics: 0 projects in intercomms status.,0,Client Flextronics: 0 projects in on going status.,0,Client Flextronics: 0 projects in blocked status.,0,Client Flextronics: 0 projects in delayed status.,0,Client Flextronics: 0 projects in completed status.],[Hyflux Limited,0,Client Hyflux Limited: 0 projects in start status.,0,Client Hyflux Limited: 0 projects in intercomms status.,0,Client Hyflux Limited: 0 projects in on going status.,0,Client Hyflux Limited: 0 projects in blocked status.,0,Client Hyflux Limited: 0 projects in delayed status.,0,Client Hyflux Limited: 0 projects in completed status.],[LiveTV,0,Client LiveTV: 0 projects in start status.,0,Client LiveTV: 0 projects in intercomms status.,0,Client LiveTV: 0 projects in on going status.,0,Client LiveTV: 0 projects in blocked status.,0,Client LiveTV: 0 projects in delayed status.,1,Client LiveTV: 1 projects in completed status.],[Maxima FM,1,Client Maxima FM: 1 projects in start status.,0,Client Maxima FM: 0 projects in intercomms status.,0,Client Maxima FM: 0 projects in on going status.,0,Client Maxima FM: 0 projects in blocked status.,0,Client Maxima FM: 0 projects in delayed status.,0,Client Maxima FM: 0 projects in completed status.],[Phillips 66,0,Client Phillips 66: 0 projects in start status.,0,Client Phillips 66: 0 projects in intercomms status.,0,Client Phillips 66: 0 projects in on going status.,0,Client Phillips 66: 0 projects in blocked status.,0,Client Phillips 66: 0 projects in delayed status.,0,Client Phillips 66: 0 projects in completed status.],[ProTV,0,Client ProTV: 0 projects in start status.,0,Client ProTV: 0 projects in intercomms status.,1,Client ProTV: 1 projects in on going status.,0,Client ProTV: 0 projects in blocked status.,0,Client ProTV: 0 projects in delayed status.,0,Client ProTV: 0 projects in completed status.],[Qatar Airlines,0,Client Qatar Airlines: 0 projects in start status.,0,Client Qatar Airlines: 0 projects in intercomms status.,1,Client Qatar Airlines: 1 projects in on going status.,0,Client Qatar Airlines: 0 projects in blocked status.,0,Client Qatar Airlines: 0 projects in delayed status.,0,Client Qatar Airlines: 0 projects in completed status.],[Telefonica R&D,0,Client Telefonica R&D: 0 projects in start status.,0,Client Telefonica R&D: 0 projects in intercomms status.,0,Client Telefonica R&D: 0 projects in on going status.,0,Client Telefonica R&D: 0 projects in blocked status.,0,Client Telefonica R&D: 0 projects in delayed status.,0,Client Telefonica R&D: 0 projects in completed status.],[Wal-Mart Stores,27,Client Wal-Mart Stores: 27 projects in start status.,0,Client Wal-Mart Stores: 0 projects in intercomms status.,0,Client Wal-Mart Stores: 0 projects in on going status.,0,Client Wal-Mart Stores: 0 projects in blocked status.,0,Client Wal-Mart Stores: 0 projects in delayed status.,0,Client Wal-Mart Stores: 0 projects in completed status.],]);
  // Create and draw the visualization.
  new google.visualization.ColumnChart(document.getElementById('visualization')).
  draw(data,
       {title:'Yearly Coffee Consumption by Country',
        isStacked: true,
        width:600, height:400,
        vAxis: {title: 'number or projects'},
        hAxis: {title: 'Clients'}}
      );
}
*/