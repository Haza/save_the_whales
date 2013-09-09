<?php
/**
 * @file
 * Implementation of DrupalUserMigration for Drupal 7 sources.
 */

class WhaleUser7Migration extends DrupalUser7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    // Probably too much stuff here.
    $this->addSimpleMappings(array(
      'field_biography',
      'field_company',
      'field_events',
      'field_icq',
      'field_jabber',
      'field_msn',
      'field_nickname',
      'field_picture',
      'field_picture:alt',
      'field_picture:title',
      'field_picture:width',
      'field_picture:height',
      'field_realname',
      'field_website',
      'field_website:title',
      'field_website:attributes',
      'field_planete_rss',
      'field_planete_rss:title',
      'field_planete_rss:attributes',
      'field_biography:language',
      'field_icq:language',
      'field_jabber:language',
      'field_nickname:language',
      'field_realname:language',
      'field_website:language',
      'field_planete_rss:language',
    ));
    $this->destination = new DrupalDestinationUser();
  }

  /**
   * Implementation of Migration::complete().
   *
   * @param $account
   * @param $row
   */
  public function complete($account, $row) {
    parent::complete($account, $row);

    // The incoming password was encrypted - user_save added an extra round of
    // encryption, we need to replace that with the original encrypted value.
    $account->pass = $row->pass;
    db_update('users')
      ->fields(array('pass' => $account->pass))
      ->condition('uid', $account->uid)
      ->execute();
  }

  /**
   * Query for the basic user data. Same query is used for all currently-supported
   * versions of Drupal.
   *
   * @return QueryConditionInterface
   */
  protected function query() {
    // Do not attempt to migrate the anonymous or admin user rows.
    $query = Database::getConnection('legacy', $this->sourceConnection)
             ->select('users', 'u')
             ->fields('u')
             ->condition('u.uid', SAVE_THE_WHALES_USER_START, '>');
    return $query;
  }
}
