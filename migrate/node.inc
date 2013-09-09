<?php

/**
 * Common mappings for the Drupal 6 node migrations.
 */
abstract class SaveTheWhalesNodeMigration extends DrupalNode7Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->removeFieldMapping('body:summary', 'body:summary');
    $this->removeFieldMapping('body:format', 'body:format');
    $this->removeFieldMapping('body', 'body');
    $this->removeFieldMapping('body:language', 'body:language');
    $this->removeFieldMapping('pathauto', 'pathauto');

  }

  /**
   * Query for basic node fields from Drupal 7.
   *
   * @return QueryConditionInterface
   */
  protected function query() {
    $query = Database::getConnection('legacy', $this->sourceConnection)
             ->select('node', 'n')
             ->fields('n', array('nid', 'vid', 'language', 'title', 'uid',
               'status', 'created', 'changed', 'comment', 'promote', 'sticky',
               'tnid', 'translate'))
             ->condition('type', $this->sourceType)
             ->condition('nid', SAVE_THE_WHALES_NODE_START, '>');
    return $query;
  }
}


class ForumWhalesMigration extends SaveTheWhalesNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addSimpleMappings(array(
      'taxonomy_forums',
      'taxonomy_vocabulary_4',
      'taxonomy_vocabulary_5',
      'body',
      'field_workflow_status',
    ));
  }
}

class AnnuaireWhalesMigration extends SaveTheWhalesNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addSimpleMappings(array(
      'field_adresse',
      'field_asso_member',
      'field_description',
      'field_forme_juridique',
      'field_logo',
      'field_mail',
      'field_member',
      'field_region',
      'field_showcase',
      'field_showcase:title',
      'field_showcase:attributes',
      'field_siren',
      'field_taille',
      'field_telephone',
      'field_type_de_service',
      'field_url',
      'field_url:title',
      'field_url:attributes',
    ));

  }
}

class OffreWhalesMigration extends SaveTheWhalesNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addSimpleMappings(array(
      'body',
      'field_info_contact',
      'field_nature_poste',
      'field_region',
      'field_societe',
      'field_teletravail',
      'field_temps_publication',
      'field_type_contrat',
    ));
  }
}
