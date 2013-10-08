/* based on
   http://www.rsc-ne-scotland.org.uk/mashe/2008/06/generating-charts-from-accessible-data-tables-using-the-google-charts-api
   which was based on
   http://www.wait-till-i.com/2008/01/08/generating-charts-from-accessible-data-tables-using-the-google-charts-api

   see the reference for Google Charts API:
   http://code.google.com/apis/chart/docs/chart_params.html

*/

$(document).ready(function() {
  generateCharts();
});

function generateCharts() {
  /* variables */
  var triggerClass = 'tochart';
  var chartClass = 'fromtable';
  var hideClass = 'dont-hide';
  var chartColor = '339933';
  var chartSize = '450x150';
  var chartType = 'p3';
  var dataPointSize = '0';
  var niceCol = new Array('4286EF','DE3810','FF9A00','008200','636563','4A41CE','CE49C6','D6AE00','31659C');

  var toTableClass = 'totable';
  var tableClass = 'generatedfromchart';
  /* end variables */

  var tables = document.getElementsByTagName('table');
  var sizeCheck = /\s?size([^\s]+)/;
  var colCheck = /\s?color([^\s]+)/;
  var chtCheck = /\s?type([^\s]+)/;
  var dptCheck = /\s?pointsize([^\s]+)/;
  for (var i=0; tables[i]; i++) {
    var t = tables[i];
    var c = t.className;
    var data = [];
    var legend = [];
    if (t.caption) {
      var captionText = t.caption.innerHTML;
      captionText = captionText.replace(/<br>/gi,'|');
      captionText = captionText.replace(/ /gi, '+');
    }
    else {
      var captionText = '';
    }
    if (c.indexOf(triggerClass) !== -1) {
      var size = sizeCheck.exec(c);
      size = size ? size[1] : chartSize;
      var col = colCheck.exec(c);
      col = col ? col[1] : chartColor;
      var cht = chtCheck.exec(c);
      cht = cht ? cht[1] : chartType;
      var dpt = dptCheck.exec(c);
      dpt = dpt ? dpt[1] : dataPointSize;
      var charturl = 'http://chart.apis.google.com/chart?cht='+cht+'&chco=' + col + '&chs=' + size + '&chd=t:';
      t.className += ' '+ hideClass;
      data = readTableData(t,'tbody');
      var yMax = findLargest(data);
      var yMarks = new Array(yMax/6,yMax/6*2,yMax/6*3,yMax/6*4,yMax/6*5,yMax);
      data = convertTableToPerc(data,yMax);
      legend = readTableData(t,'thead');
      tData = tDataTranspose(data);
      var tString = '';
      for (var k=1; k<tData.length; k++) {
        tString += tData[k].join(',')+'|';
      }
      tString = tString.substr(0,tString.length-1);
      charturl += tString;
      charturl += '&chxt=x,y&chxr=1,0,'+yMax;
      charturl += addDataLabels(tData,cht);
      if (cht=='lc') {
        charturl += '|1:|'+yMarks.join('|')+'&chxp=1,'+yMarks.join(',');
        charturl += addDataPoints(tData,'o',dpt);
        charturl += '&chco='+niceCol.slice(0,tData[0].length).join(',');
        charturl += '&chg=0,16.666667';
      }
      if (cht=='bvg') {
        charturl += '&chco='+niceCol.slice(0,tData[0].length).join(',');
        charturl += '&chbh=a';  // auto bar width
      }
      var chart = document.createElement('img');
      chart.setAttribute('src',charturl + '&chdl='+legend[0].slice(1).join('|')+'&chtt='+captionText+'&chts=000000,12');
      chart.setAttribute('alt',t.getAttribute('summary'));
      chart.className = chartClass;
      t.parentNode.insertBefore(chart,t);
    }
  }
}

function readTableData(tbl,tPart) {
  tbl.tabledata = new Array(); // initialize array
  bodyrows = tbl.getElementsByTagName(tPart)[0].getElementsByTagName('tr'); // get collection of table body rows.
  for (var i=0; i<bodyrows.length; i++) // iterate through table rows
  {
    tbl.tabledata.push(new Array()); //create new array for row elements and push it in tabledata array
    for (var j=0; j<bodyrows[i].childNodes.length; j++) // iterate through table row child nodes
    {
      var childNode = bodyrows[i].childNodes[j]; // child node to a local variable
      if (/th/i.test(childNode.nodeName) || /td/i.test(childNode.nodeName)) // if the child node is "th" or "td" (gecko throws empty text nodes in)
      {
        if (childNode.firstChild) // make sure it is not an empty node
          tbl.tabledata[i].push(childNode.firstChild.nodeValue) // assume that <td> or <th> element has no other children but the text node containing the data
        }
    }
  }
  return tbl.tabledata;
}

function findLargest(aTabledata) {
  var largestVal = 0;
  for (var i=0; i<aTabledata.length; i++)
  {
    for (var j=1; j<aTabledata[i].length; j++)
    {
      if (Number(aTabledata[i][j])>largestVal)
      {
        largestVal=aTabledata[i][j];
      }
    }
  }
  numofPositions = Math.ceil(largestVal).toString().length-1;
  largestVal = Math.round(largestVal/Math.pow(10,numofPositions),0)*Math.pow(10,numofPositions);
  return largestVal;
}

function convertTableToPerc(aTabledata,aDivider) {
  for (var i=0; i<aTabledata.length; i++)
  {
    for (var j=1; j<aTabledata[i].length; j++)
    {
      aTabledata[i][j]=Math.round((aTabledata[i][j]/aDivider)*100);
    }
  }
  return aTabledata;
}

function tDataTranspose(tArray) {
  tOut = new Array();
  for (var i=0; i<tArray[0].length; i++)
  {
    tOut.push(new Array());
    for (var j=0; j<tArray.length; j++)
    {
      tOut[i].push(tArray[j][i]);
    }
  }
  return tOut;
}

function addDataPoints(tArray,style,size) {
  var stringOut = '&chm='
  for (var i=1; i<tArray.length; i++) {
    for (var j=0; j<tArray[i].length; j++) {
      stringOut += style+','+niceCol[i-1]+','+[i-1]+','+[j]+'.0,'+size+'|';
    }
  }
  stringOut = stringOut.substr(0,stringOut.length-1);
  return stringOut;
}

function addDataLabels(tArray,cType) {
  var stringOut = '&chxl=0:|'
  if (cType=="lc" || cType=="bvg") {
    stringOut += tArray[0].join('|').replace(/ /gi, '+');
  }
  else {
    for (var i=0,sum=0; i<tArray[1].length; sum+=tArray[1][i++]);
    for (var j=0; j<tArray[0].length; j++) {
      stringOut += tArray[0][j].replace(/ /gi, '+') + '+('+Math.round(tArray[1][j]/sum*100)+'%)|';
    }
  }
  return stringOut;
}

