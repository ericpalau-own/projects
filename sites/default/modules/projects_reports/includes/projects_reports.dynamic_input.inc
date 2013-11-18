<?php 
/**
 * Projects reports
 */
function projects_reports_clients_page_3() {
  $output = '';
  
  // Add input form 
  $output .= drupal_render(drupal_get_form('projects_reports_dynamic_input_form'));
  
  return $output;
}

/**
 * Input form to generate the needed graph
 */
function projects_reports_dynamic_input_form($form, &$form_state) {
	
	$form['input_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Graph input data'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
	);
	
	// Content type dropdown list
  $form['input_form']['ct'] = array(
    '#title' => t('Province'),
    '#type' => 'select',
    '#options' => _load_ct_types(),
    '#ajax' => array(
      'event'=>'change',
      'callback' =>'reports_ajax_dropdown_taxonomy',
      'wrapper' => 'tax-wrapper',
    ),
  );

  // Wrapper for city dropdown list
  $form['input_form']['wrapper'] = array(
    '#prefix' => '<div id="tax-wrapper">',
    '#suffix' => '</div>',
  );

  // Options for city dropdown list
  $options = array('- Select city -');
  if (isset($form_state['values']['ct'])) {
    // Pre-populate options for city dropdown list if province id is set
    $options = _load_ct_tax_types($form_state['values']['ct']);
  }

  // Province dropdown list
  $form['input_form']['wrapper']['tax'] = array(
    '#title' => t('Taxonomy'),
    '#type' => 'select',
    '#options' => $options,
  );
	
	$form['input_form']['start_date'] = array(
	 '#title' => t('Start date'),
	 '#type' => 'date',
	 '#description' => t('This start date means when the project / engagement has been passed from "to do" status to the first status (start in project type, in discussion in engagement type).'),
	);
	$form['input_form']['end_date'] = array(
	 '#title' => t('End date'),
	 '#type' => 'date',
	 '#description' => t('This end date means when the project / engagement has been passed the completed / deployment status.'),
	);
	
	$form['input_form']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Build graph'),
  );
  
  if (isset($form_state['storage']['graph'])) {
  	$form['graph'] = $form_state['storage']['graph'];
  }
  
	return $form;
}

/**
 * Function for handling ajax request
 */
function reports_ajax_dropdown_taxonomy($form, $form_state) {
  // Return the dropdown list including the wrapper
  return $form['input_form']['wrapper'];
}

/**
 * Function for populating province
 */
function _load_ct_types() {

    $types['any'] = '- Select type -';
    $types['project'] = 'Projects';
    $types['engagement'] = 'Commercial Engagements';

  return $types;
}

/**
 * Function for populating city
 */
function _load_ct_tax_types($ct_id) {
  $tax = array('- Select tax -');

  switch ($ct_id) {
  	case 'project':
		  $tax[3] = 'Clients';
		  $tax[2] = 'Team';
		  break;
  	case 'engagement':
		  $tax[3] = 'Clients';
		  $tax[7] = 'engagement type';
		  break;
  		
  }
  return $tax;
}

function projects_reports_dynamic_input_form_submit($form, &$form_state) {
	// Get needed values from the form to generate the graph
	$project = $form_state['values']['ct'];
	$tax = $form_state['values']['tax'];
	$start_date = $form_state['values']['start_date'];
	$end_date = $form_state['values']['end_date'];
	
	// Get graph data
	$graph = projects_reports_get_graph_data($project, $tax);
	
	// static data for chart
	$chart = array(
    '#type' => 'chart',
    '#chart_type' => 'bar',
    '#title' => t('reports graph'),
    '#chart_library' => 'highcharts',
    '#stacking' => TRUE,
    '#height' => '500',
  );
  
  // Add graph in $form_state['storage']
	$form_state['storage']['graph'] = $chart + $graph;  
	$form_state['rebuild'] = TRUE;
}
