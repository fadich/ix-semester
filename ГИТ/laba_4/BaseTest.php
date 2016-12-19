<?php

namespace app\components\HelpClasses\test;


abstract class BaseTest extends \PHPUnit_Framework_TestCase
{
    /** @var array $_results  The results of tests */
    protected $_results = [];

    public function viewResults()
    {
        if (!empty($this->_results)) {
            return implode("<br><br>", $this->implodeResults());
        }
        return null;
    }

    public function report(string $description, string $key, string $message = null)
    {
        $this->_results[] = [
            'description' => $description,
            'key'         => $key,
            'message'     => $message,
        ];
    }

    protected function implodeResults()
    {
        $results = [];
        foreach ($this->_results as $key => $result) {
            $results[] = "- Test # " . ($key + 1) . ": \nDescription: " . $result['description'] . ";\nResult: " . $result['key'] . ($result['message'] ? ";\nMessage: " . $result['message'] : "");
        }
        return $results;
    }
}