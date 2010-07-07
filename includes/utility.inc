<?php
// $Id$

/**
 * @file
 * Miscellaneous functions.
 */

/**
 * Drupal-friendly var_export().
 *
 * @param $var
 *   The variable to export.
 * @param $prefix
 *   A prefix that will be added at the begining of every lines of the output.
 * @return
 *   The variable exported in a way compatible to Drupal's coding standards.
 */
function drupal_var_export($var, $prefix = '') {
  if (is_array($var)) {
    if (empty($var)) {
      $output = 'array()';
    }
    else {
      $output = "array(\n";
      // Don't export keys if the array is non associative.
      $export_keys = array_values($var) != $var;
      foreach ($var as $key => $value) {
        $output .= '  ' . ($export_keys ? drupal_var_export($key) . ' => ' : '') . drupal_var_export($value, '  ', FALSE) . ",\n";
      }
      $output .= ')';
    }
  }
  else if (is_bool($var)) {
    $output = $var ? 'TRUE' : 'FALSE';
  }
  else if (is_string($var)) {
    $line_safe_var = str_replace("\n", '\n', $var);
    if (strpos($var, "\n") !== FALSE || strpos($var, "'") !== FALSE) {
      // If the string contains a line break or a single quote, use the
      // double quote export mode. Encode backslash and double quotes and
      // transform some common control characters.
      $var = str_replace(array('\\', '"', "\n", "\r", "\t"), array('\\\\', '\"', '\n', '\r', '\t'), $var);
      $output = '"' . $var . '"';
    }
    else {
      $output = "'" . $var . "'";
    }
  }
  else {
    $output = var_export($var, TRUE);
  }

  if ($prefix) {
    $output = str_replace("\n", "\n$prefix", $output);
  }

  return $output;
}