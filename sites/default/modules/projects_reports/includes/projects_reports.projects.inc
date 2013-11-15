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
  
  // Get workflow states
  $workflows = workflow_get_workflow_states_by_type('project');
  // Delete creation workflow and to do workflow, not needed
  unset($workflows[0]);
  unset($workflows[1]);
  //Reverse the array to put in the correct order
  $workflows = array_reverse($workflows);
  // Get clients list
  $clients = taxonomy_get_tree(3);

  // Prepare current and previous months to add them to the label
  $current_month = date('M',time());
  $prev_month = date('M', strtotime("last month"));
  
  // Fill chart data
  foreach ($workflows as $key => $wf) {
    $row = array();
    $label = '';
    // Prepare label
    $label = (($wf->state == 'completed') ? $wf->state .' in '.$prev_month : $wf->state .' in '.$current_month);
    $chart[$wf->state] = array(
     '#type' => 'chart_data',
     '#title' => $label,
    );
    // Prepare each row data
    foreach ($clients as $client) {
      $nodes_related_pro = projects_reports_taxonomy_select_nodes_by_state($client->tid, false, false, array(), $wf->sid);
      //Store them in the row array
      $row[] = count($nodes_related_pro);
    }
    // Add row array to the chart
    $chart[$wf->state]['#data'] = $row;
  }
  
  // Prepare X labels
  $xaxis = array();
  foreach ($clients as $key => $cl) {
    $xaxis[] = $cl->name;
  }
  $chart['xaxis'] = array(
    '#type' => 'chart_xaxis',
    '#labels' => $xaxis,
    '#labels_rotation' => 60
  );

  return drupal_render($chart);
  
}

/**
 * Get tabla data
 * @param csv boolean Return data to be applied to the csv
 * @return Array
 *    'header' => table header 
 *    'rows' => all rows from the table
 */
function projects_reports_get_table_data($csv = FALSE){
  // Get clients list
  $clients = taxonomy_get_tree(3);
  
  // Get workflow states
  $workflows = workflow_get_workflow_states_by_type('project');
  
  // Unset creation state and to do state
  unset($workflows[0]);
  unset($workflows[1]);

  // Prepare table header
  $header = array();

  // First header item is static. It will contain the status column
  $header[] = t('status');  
  
  // Add a header entry foreach client
  foreach ($clients as $client) {
    // Add client to the header list
    $header[] = $client->name;
  }
  
  // Last header item is static. It will contain the sum of each row, the status total projects
  if ($csv) {
    $header[] = t('total');
  } 
  else {
    $header[] = array(
      'data' => t('total'),
      'class' => 'highlight'
    );
  }
    
  // Initialize table data.  
  $rows = array();
  
  // Prepare content data 
  // Each row will be a workflow status
  foreach ($workflows as $key => $wf) {
    $row = array();
    // Initialize total project cont for workflow status
    $total_project_cont = 0;
    
    // The first item for each row will be the workflow status label
    $row[] = $wf->state;
    
    // Foreach client, we check the number of projects for the current state and add them to the row array
    foreach ($clients as $client) {
      // We init the project cont
      $nodes_related_pro = 0;
      // Get all project from client $client with the status $wf->sid
      $nodes_related_pro = projects_reports_taxonomy_select_nodes_by_state($client->tid, false, false, array(), $wf->sid);
      //Store them in the row array
      $row[] = count($nodes_related_pro);
      // We sum the project cont to the total project cont for current workflow status
      $total_project_cont += count($nodes_related_pro);
    }
    
    if ($csv) {
      // The last item of the row will be the sum of all project of the current state
      $row[] = $total_project_cont;
    } 
    else {
      $row[] = array(
        'data' => $total_project_cont,
        'class' => 'highlight'
      );
    }
    // Add row to the total rows array
    $rows[] = $row;
  }
  
  return array('header' => $header, 'rows' => $rows);
}

/**
 * Process requests for 'reports/clients' path.
 */
function projects_reports_clients_table() {
  // Get table data
  $table_data = projects_reports_get_table_data();
  
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

