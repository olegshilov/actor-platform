/*
 * Copyright (C) 2015-2016 Actor LLC. <https://actor.im>
 */

import { forEach, map, debounce, isFunction } from 'lodash';

import React, { Component, PropTypes } from 'react';
import { Container } from 'flux/utils';
import Scrollbar from '../common/Scrollbar.react';

import MessageActionCreators from '../../actions/MessageActionCreators';

import VisibilityStore from '../../stores/VisibilityStore';
import DialogStore from '../../stores/DialogStore';
import MessageStore from '../../stores/MessageStore';

import DefaultMessageItem from './messages/MessageItem.react';
import MessagesList from './MessagesList.react';


let _delayed = [];
let flushDelayed = () => {
  forEach(_delayed, (p) => MessageActionCreators.setMessageShown(p.peer, p.message));
  _delayed = [];
};

let flushDelayedDebounced = debounce(flushDelayed, 30, {maxWait: 100});

class MessagesSection extends Component {
  static propTypes = {
    messages: PropTypes.array.isRequired,
    overlay: PropTypes.array.isRequired,
    peer: PropTypes.object.isRequired,
    isMember: PropTypes.bool.isRequired,
    onScroll: PropTypes.func.isRequired
  };

  static contextTypes = {
    delegate: PropTypes.object
  };

  static getStores() {
    return [MessageStore, VisibilityStore]
  }

  static calculateState() {
    return {
      selectedMessages: MessageStore.getSelected(),
      isAllMessagesLoaded: MessageStore.isLoaded(),
      isAppVisible: VisibilityStore.isAppVisible()
    }
  }

  componentDidUpdate() {
    const { isAppVisible } = this.state;
    if (isAppVisible) {
      flushDelayed();
    }
  };

  onMessageSelect = (rid) => {
    const { selectedMessages } = this.state;
    if (selectedMessages.has(rid)) {
      MessageActionCreators.setSelected(selectedMessages.remove(rid));
    } else {
      MessageActionCreators.setSelected(selectedMessages.add(rid));
    }
  };

  onMessageVisibilityChange = (message, isVisible) => {
    const { peer } = this.props;

    if (isVisible) {
      _delayed.push({peer, message});
      if (VisibilityStore.isAppVisible()) {
        flushDelayedDebounced();
      }
    }
  };

  getComponents() {
    const {dialog, messages} = this.context.delegate.components;
    if (dialog && dialog.messages && isFunction(dialog.messages.message)) {
      return {
        MessageItem: dialog.messages.message
      };
    }

    return {
      MessageItem: DefaultMessageItem
    };
  }

  render() {
    const { peer, overlay, messages, isMember } = this.props;
    const { selectedMessages, isAllMessagesLoaded } = this.state;

    const components = this.getComponents();

    return (
      <Scrollbar onScroll={this.props.onScroll} ref="messagesScroll">
        <MessagesList
          peer={peer}
          overlay={overlay}
          messages={messages}
          selectedMessages={selectedMessages}
          isMember={isMember}
          isAllMessagesLoaded={isAllMessagesLoaded}
          components={components}
          onSelect={this.onMessageSelect}
          onVisibilityChange={this.onMessageVisibilityChange}
        />
      </Scrollbar>
    );
  }
}

export default Container.create(MessagesSection, {pure: false, withProps: true});
