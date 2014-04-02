<?php

/**
 * Example question type.
 */
class QuizzQuestionSimple extends QuizzQuestionBase  {

  /**
   * Implements EntityBundlePluginProvideFieldsInterface::fields().
   */
  static function fields() {
    $fields = parent::fields();

    $fields['cle_name']['field'] = array(
      'type' => 'text',
      'cardinality' => 1,
    );
    $fields['cle_name']['instance'] = array(
      'label' => t('Name'),
      'required' => 1,
      'settings' => array(
        'text_processing' => '0',
      ),
      'widget' => array(
        'module' => 'text',
        'type' => 'text_textfield',
        'settings' => array(
          'size' => 20,
        ),
      ),
    );

    return $fields;
  }

  /**
   * Implements QuizzQuestionInterface::accessDetails().
   */
  public function accessDetails() {
    // Just display the name field.
    $output = field_view_field('quizz_question', $this, 'cle_name');
    return drupal_render($output);
  }

}
