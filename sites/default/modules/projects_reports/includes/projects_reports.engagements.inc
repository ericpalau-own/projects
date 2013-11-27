<?php 
/**
 * Projects reports
 */
function projects_reports_clients_page_2() {
  $output = '';
  
  // Add table
  $output .= projects_reports_clients_table_2();

  // Add highcharts graph
  $output .= projects_reports_clients_graph_2();
  
  return $output;
}


/**
 * Highcharts graph
 */
function projects_reports_clients_graph_2() {
  $chart = array(
    '#type' => 'chart',
    '#chart_type' => 'bar',
    '#title' => t('Engagements reports graph'),
    '#chart_library' => 'highcharts',
    '#stacking' => TRUE,
    '#height' => '500',
  );
  
  $graph = projects_reports_get_graph_data('engagement', 3);
  
  $total = $graph + $chart;

  return drupal_render($total);
  
}



/**
 * Process requests for 'reports/clients' path.
 */
function projects_reports_clients_table_2() {
  // Get table data
  $table_data = projects_reports_get_table_data('engagement', 3);
  
  // Prepare table to theme it
  $variables = array(
    'header' => $table_data['header'],
    'rows' => $table_data['rows'],
    'attributes' => array(),
    'caption' => '',
    'colgroups' => array(),
    'sticky' => '',
    'empty' => t('No engagements found'),
  );
  
  // Prepare link to be exported
  $csv_link = l('Download as csv', 'reports/clients/engagements_csv');
  
  // Return themed table
  return $csv_link . theme_table($variables);
}

	