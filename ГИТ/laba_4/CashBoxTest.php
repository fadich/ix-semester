<?php

namespace app\models\cashbox;


use app\components\HelpClasses\test\BaseTest;

class CashBoxTest extends BaseTest
{
    /** @var BaseCashBox $_cash */
    protected $_cash;

    public function testDepositCashBox()
    {
        $this->_cash = new CashBox(132);
        try {
            $this->assertClassHasAttribute('value', CashBox::class);
            $this->report('Check the "value" property', 'PASSED');
        } catch (\PHPUnit_Framework_ExpectationFailedException $exception) {
            $this->report('Check the "value" property', 'FAILED', $exception->getMessage());
        }
        try {
            $this->assertClassHasAttribute('comment', CashBox::class);
            $this->report('Check the "comment" property', 'PASSED');
        } catch (\PHPUnit_Framework_ExpectationFailedException $exception) {
            $this->report('Check the "comment" property', 'FAILED', $exception->getMessage());
        }
        foreach ($this->providerDepositCashBox() as $attributes) {
            try {
                $this->assertEquals($attributes['expectation'], $this->_cash->deposit($attributes));
//                echo "<pre>"; var_export($this->_cash->attributes); echo "</pre>";
                $this->report('Deposit CashBox', 'PASSED');
            } catch (\PHPUnit_Framework_ExpectationFailedException $exception) {
//                echo "<pre>"; var_export($this->_cash->attributes); echo "</pre>";
                $this->report('Deposit CashBox', 'FAILED', $exception->getMessage());
            }
        }
        return $this->viewResults();
    }

    protected function providerDepositCashBox()
    {
        return [
            [
                'expectation' => true,
                'value'       => 15.15,
                'comment'     => 'Comment',
            ],
            [
                'expectation' => true,
                'value'       => 150.15,
                'comment'     => 'Комментарий к пополнению',
            ],
            [
                'expectation' => false,
                'value'       => 0,
                'comment'     => '',
            ],
            [
                'expectation' => false,
                'value'       => 15.9,
                'comment'     => '',
            ],
            [
                'expectation' => false,
                'value'       => 0,
                'comment'     => 'Comment',
            ],
            [
                'expectation' => false,
                'value'       => 99999999999,
                'comment'     => 'Comment',
            ],
            [
                'expectation' => false,
                'value'       => 296.08,
                'comment'     => 'CommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentComment
                              CommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentCommentComment',
            ],
            [
                'expectation' => true,
                'value'       => (rand() * rand() / rand()) * rand(-1, 1),
                'comment'     => \Yii::$app->security->generateRandomString(rand(0, 180)),
            ],
        ];
    }
}
