<?php

/**
 * @file
 * Abstract and interface plugin implementation.
 */

/**
 * Provide a separate Exception so it can be caught separately.
 */
class QuizzQuestionException extends Exception { }

/**
 * Ensures basic required behavior for a question.
 *
 * EntityBundlePluginProvideFieldsInterface also mandates a fields() method.
 */
interface QuizzQuestionInterface extends EntityBundlePluginProvideFieldsInterface {

  /**
   * Provides the question form.
   *
   * @param $form
   *   The question form. Might be embedded in another form through
   *   Inline Entity Form.
   * @param $form_state
   *   The form state of the complete form.
   *   Always use drupal_array_get_nested_value() instead of accessing
   *   $form_state['values'] directly.
   */
  public function form(&$form, &$form_state);

  /**
   * Validates the question form.
   *
   * @param $form
   *   The question form. Might be embedded in another form through
   *   Inline Entity Form, so form['#parents'] needs to be taken into account
   *   when fetching values and setting errors.
   * @param $form_state
   *   The form state of the complete form.
   *   Always use drupal_array_get_nested_value() instead of accessing
   *   $form_state['values'] directly.
   */
  public function formValidate($form, &$form_state);

  /**
   * Submits the question form.
   *
   * @param $form
   *   The question form. Might be embedded in another form through
   *   Inline Entity Form, so form['#parents'] needs to be taken into account
   *   when fetching values and setting errors.
   * @param $form_state
   *   The form state of the complete form.
   *   Always use drupal_array_get_nested_value() instead of accessing
   *   $form_state['values'] directly.
   */
  public function formSubmit(&$form, $form_state);

}


/**
 * question base class.
 *
 */
abstract class QuizzQuestionBase extends Entity implements QuizzQuestionInterface, EntityBundlePluginValidableInterface {

  /**
   * The question id.
   *
   * @var integer
   */
  public $question_id;

  /**
   * The revision id.
   *
   * @var integer
   */
  public $revision_id;

  /**
   * The question type (bundle).
   *
   * @var string
   */
  public $type;

  /**
   * The question status.
   *
   * @var integer
   */
  public $status = 1;

  /**
   * Question metadata wrapper.
   *
   * @var EntityDrupalWrapper
   */
  public $wrapper;

  /**
   * Constructor.
   *
   * @see Entity::__construct()
   */
  public function __construct(array $values = array(), $entityType = NULL) {
    parent::__construct($values, 'quizz_question');
    $this->wrapper = entity_metadata_wrapper($this->entityType, $this);
  }

  /**
   * Implements EntityBundlePluginProvideFieldsInterface::fields().
   */
  static function fields() {
    $fields = array();

    return $fields;
  }

  /**
   * Implements QuizzQuestionInterface::form().
   */
  public function form(&$form, &$form_state) {
    field_attach_form('quizz_question', $this, $form, $form_state, LANGUAGE_NONE);
  }

  /**
   * Implements QuizzQuestionInterface::formValidate().
   */
  public function formValidate($form, &$form_state) {
    field_attach_form_validate('quizz_question', $this, $form, $form_state);
  }

  /**
   * Implements QuizzQuestionInterface::formSubmit().
   */
  public function formSubmit(&$form, $form_state) {
    field_attach_submit('quizz_question', $this, $form, $form_state);
  }

  /**
   * Overrides Entity::save().
   */
  public function save() {
    $granted = FALSE;
    if (!empty($this->quizz_question_id)) {
      $this->original = entity_load_unchanged('quizz_question', $this->question_id);
      if ($this->status > $this->original->status && $this->status == 1) {
        // The question was updated, and its status was changed to active.
        $granted = TRUE;
      }
    }
    else {
      if ($this->status == 1) {
        // The question was created with an active status.
        $granted = TRUE;
      }
    }
    // do something with granted.
    parent::save();
  }

  /**
   * Implements EntityBundlePluginValidableInterface::isValid().
   */
  public static function isValid() {
    return TRUE;
  }
}
