<?php

/**
 * @file
 * Contains admin menu callbacks for the Quizz Question module.
 */

/**
 * Settings form callback.
 */
function quizz_question_ui_settings_form($form, &$form_state) {

  $form['todo'] = array(
    '#markup' => t('Todo ?.'),
  );

  $form = system_settings_form($form);
  return $form;
}

/**
 * Generates the profile type editing form.
 */
function quizz_question_ui_type_form($form, &$form_state, $profile_type, $op = 'edit') {
  if ($op == 'clone') {
    $profile_type->label .= ' (cloned)';
    $profile_type->type .= '_clone';
  }
  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => isset($profile_type->label) ? $profile_type->label : '',
  );
  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($profile_type->type) ? $profile_type->type : '',
     '#machine_name' => array(
      'exists' => 'quizz_question_get_type_plugins',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this profile type. It must only contain lowercase letters, numbers, and underscores.'),
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save question type'),
    '#weight' => 40,
  );
  return $form;
}
/**
 * Form API submit callback for the type form.
 */
function quizz_question_ui_type_form_submit(&$form, &$form_state) {
  $profile_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  $profile_type->save();
  $form_state['redirect'] = 'admin/structure/quizz/question-types';
}

/**
 * Settings form callback.
 */
function quizz_question_ui_types_settings_form($form, &$form_state) {


  foreach(quizz_question_get_type_plugins() as $key => $plugin) {
    $types[$key] = $plugin['title'];
  }
  if (empty($types)) {
    return $form;
  }
  $form[$key] = array(
    '#type' => 'checkboxes',
    '#title' => t('List of question types'),
    '#options' => $types,
  );

  $form = system_settings_form($form);
  return $form;
}
