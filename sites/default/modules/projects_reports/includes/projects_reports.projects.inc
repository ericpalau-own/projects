<?php 
/**
 * Projects reports
 */
function projects_reports_clients_page() {
  $output = '';
  
  // Add table
  $output .= projects_reports_clients_table();

  // Add highcharts graph
  $output .= projects_reports_clients_graph();
  
  return $output;
}


/**
 * Highcharts graph
 */
function projects_reports_clients_graph() {
  $chart = array(
    '#type' => 'chart',
    '#chart_type' => 'bar',
    '#title' => t('Projects reports graph'),
    '#chart_library' => 'highcharts',
    '#stacking' => TRUE,
    '#height' => '500',
  );
  
  $graph = projects_reports_get_graph_data('project', 3);
  
  $total = $graph + $chart;

  return drupal_render($total);
  
}



/**
 * Process requests for 'reports/clients' path.
 */
function projects_reports_clients_table() {
  // Get table data
  $table_data = projects_reports_get_table_data('project', 3);
  
  // Prepare table to theme it
  $variables = array(
    'header' => $table_data['header'],
    'rows' => $table_data['rows'],
    'attributes' => array(),
    'caption' => '',
    'colgroups' => array(),
    'sticky' => '',
    'empty' => t('No projects found'),
  );
  
  // Prepare link to be exported
  $csv_link = l('Download as csv', 'reports/clients/projects_csv');
  
  // Return themed table
  return $csv_link . theme_table($variables);
}

