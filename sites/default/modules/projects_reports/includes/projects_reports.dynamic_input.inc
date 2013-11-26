<?php 
/**
 * Projects reports
 */
function projects_reports_clients_page_3() {
  $output = '';
  
  // Add input form 
  $dynamic_form = drupal_get_form('projects_reports_dynamic_input_form');
  $output .= drupal_render($dynamic_form);
  
  return $output;
}

/**
 * Input form to generate the needed graph
 */
function projects_reports_dynamic_input_form($form, &$form_state) {
	
	// Check if the graph is generated
	$is_graph = (isset($form_state['storage']['graph']));
	
	$form['input_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Graph input data'),
    '#collapsible' => TRUE,
    '#collapsed' => (($is_graph) ? TRUE : FALSE),
	);
	
	if ($is_graph) {
		$form['ct_markup'] =array(
		  '#type' => 'item',
      '#title' => t('Content type'),
      '#markup' => $form_state['values']['ct'],
		);
		$voc = taxonomy_vocabulary_load($form_state['values']['tax']);
		$form['tax_markup'] =array(
		  '#type' => 'item',
      '#title' => t('Taxonomy'),
      '#markup' => $voc->name,
		);
		if (!empty($form_state['values']['start_date'])) {
			$form['start_date_markup'] =array(
			  '#type' => 'item',
	      '#title' => t('Start date'),
	      '#markup' => $form_state['values']['start_date'],
			);
		}
		if (!empty($form_state['values']['end_date'])) {
			$form['end_date_markup'] =array(
			  '#type' => 'item',
	      '#title' => t('End date'),
	      '#markup' => $form_state['values']['end_date'],
			);
		}
	}
	
	// Content type dropdown list
  $form['input_form']['ct'] = array(
    '#title' => t('Content type'),
    '#type' => 'select',
    '#required' => TRUE,
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
  $options = array();
  if (isset($form_state['values']['ct'])) {
    // Pre-populate options for city dropdown list if province id is set
    $options = _load_ct_tax_types($form_state['values']['ct']);
  }

  // Province dropdown list
  $form['input_form']['wrapper']['tax'] = array(
    '#title' => t('Taxonomy'),
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => $options,
  );
	$dateformat = 'Y-m-d';
	$form['input_form']['start_date'] = array(
	 '#title' => t('Start date'),
	 '#type' => 'date_popup',
	 '#date_format' => $dateformat,
   '#date_year_range' => '-3:+3',
//	 '#description' => t('This start date means when the project / engagement has been passed from "to do" status to the first status (start in project type, in discussion in engagement type).'),
	);
	$form['input_form']['end_date'] = array(
	 '#title' => t('End date'),
	 '#type' => 'date_popup',
	 '#date_format' => $dateformat,
   '#date_year_range' => '-3:+3',
//	 '#description' => t('This end date means when the project / engagement has been passed the completed / deployment status.'),
	);
	
	$form['input_form']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Build graph'),
  );
  
  if ($is_graph) {
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
    $types['project'] = 'Projects';
    $types['engagement'] = 'Commercial Engagements';

  return $types;
}

/**
 * Function for populating city
 */
function _load_ct_tax_types($ct_id) {
  $tax = array();
  switch ($ct_id) {
  	case 'project':
		  $tax[3] = 'Clients';
		  $tax[2] = 'Team';
		  $tax[1] = 'Tags';
		  break;
  	case 'engagement':
		  $tax[3] = 'Clients';
		  $tax[7] = 'Categories';
		  $tax[9] = 'Location';
		  $tax[1] = 'Tags';
		  break;
  		
  }
  return $tax;
}

function projects_reports_dynamic_input_form_validate($form, &$form_state) {
	$start_date = $form_state['values']['start_date'];
	$end_date = $form_state['values']['end_date'];

	// Check if start date and end date are set together or only one of them.
	// If only start date or end date is set, return an error saying both are needed.
	if ((!empty($start_date) && empty($end_date)) || (empty($start_date) && !empty($end_date))) {
		form_set_error('start_date', t('Please introduce both start and end date to process the graph with correct dates.'));
		form_set_error('end_date', '');
	}
	
	// Check if the end date is greater or equal than the start date. If not, raise an error
	if (!empty($start_date) && !empty($end_date) && $end_date <= $start_date) {
		form_set_error('end_date', t('End date must be greather or equal than start date. Please introduce correct dates to process the graph.'));
	}
}

function projects_reports_dynamic_input_form_submit($form, &$form_state) {
	// Get needed values from the form to generate the graph
	$project = $form_state['values']['ct'];
	$tax = $form_state['values']['tax'];
	$start_date = strtotime($form_state['values']['start_date']);
	$end_date = strtotime($form_state['values']['end_date']);
	
	// Get graph data
	$graph = projects_reports_get_graph_data($project, $tax, $start_date, $end_date, FALSE);
	
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

